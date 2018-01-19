/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <term.h>

#include "ush/shell.h"
#include "ush/pool.h"
#include "ush/eval.h"
#include "ush/var.h"

t_bool				g_shinteract = 0;
pid_t				g_shpgid;
TTY					g_shmode;
int					g_shfd = -1;
int					g_shstatus = 0;

static t_deq		g_stack_toks = { NULL, sizeof(t_tok), 0, 0, 0 };
static t_deq		*g_toks = &g_stack_toks;
static size_t		g_toks_max = 0;

static void			sigchld(int signo)
{
	(void)signo;
	sh_poolnotify();
}

static inline void	sh_init(int fd)
{
	g_shpgid = getpgrp();
	if (!(g_shinteract = (t_bool)isatty(fd)))
		return ;
	while (tcgetpgrp(fd) != g_shpgid)
		kill(-g_shpgid, SIGTTIN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, sigchld);
	g_shpgid = getpid();
	if (setpgid(g_shpgid, g_shpgid) < 0)
		sh_exit(EXIT_FAILURE, "Couldn't put the shell in its own process "
			"group");
	tcsetpgrp(fd, g_shpgid);
	tcgetattr(fd, &g_shmode);
}

inline int			sh_run(int fd)
{
	char	*ln;
	char	*it;
	int		st;

	sh_init(fd);
	sh_varscope();
	sh_poolscope();
	while (!(st = rl_getline(fd, "$> ", &ln)))
	{
		it = ln;
		g_toks->len = 0;
		g_toks->cur = 0;
		while (!(st = sh_lex(fd, g_toks, &it, &ln)))
		{
			sh_eval(fd, g_toks, &ln);
			g_toks->len = 0;
			g_toks->cur = 0;
		}
		if (st < 0)
			break ;
	}
	while (sh_varunscope())
		;
	while (sh_poolunscope())
		;
	rl_finalize(fd);
	if (st < 0)
		g_shstatus = EXIT_FAILURE;
	return (g_shstatus);
}

int					sh_exit(int exitno, char const *fmt, ...)
{
	va_list	ap;

	if (g_shfd >= 0)
		rl_finalize(g_shfd);
	rl_dtor();
	sh_envdtor();
	g_toks->len = g_toks_max;
	g_toks->cur = 0;
	ft_deqdtor(g_toks, (t_dtor)ft_sdsdtor);
	if (fmt)
	{
		va_start(ap, fmt);
		sh_verr(fmt, ap);
		va_end(ap);
	}
	if (exitno > 255)
		exit(EXIT_FAILURE);
	exit(exitno == WUT ? EXIT_FAILURE : exitno);
}
