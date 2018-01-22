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
	signal(SIGCHLD, SIG_DFL);
	g_shpgid = getpid();
	if (setpgid(g_shpgid, g_shpgid) < 0)
		sh_exit(EXIT_FAILURE, "Couldn't put the shell in its own process "
			"group");
	tcsetpgrp(fd, g_shpgid);
	tcgetattr(fd, &g_shmode);
	rl_hook(sh_poolnotify);
	rl_complete(sh_complete);
}

static char			*sh_prompt(char *prompt, char *buf)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	*r;
	char	*home;

	if (!(p = getcwd(cwd, PATH_MAX)))
	{
		THROW(WUT);
		return (NULL);
	}
	if ((home = sh_getenv("HOME")) && ft_strbegw(home, p))
	{
		if (p[l = ft_strlen(home)] != '\0')
			ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
		else
			p[1] = '\0';
		*p = '~';
	}
	r = buf;
	while (*p)
		if (*p == '/' && *(p + 1) && (home = ft_strchr(p + 1, '/')))
		{
			*r++ = *p++;
			*r++ = *p;
			p = home;
		}
		else
			*r++ = *p++;
	ft_strcpy(r, prompt);
	return (buf);
}

#define SH_PROMPT() (g_shstatus==0?" \033[32m❯\033[0m ":" \033[31m❯\033[0m ")

inline int			sh_run(int fd)
{
	char	*ln;
	char	*it;
	int		st;
	char	buf[PATH_MAX];

	sh_init(fd);
	sh_varscope();
	sh_poolscope();
	while (!(st = rl_getline(fd, sh_prompt(SH_PROMPT(), buf), &ln)))
	{
		it = ln;
		g_toks->len = 0;
		g_toks->cur = 0;
		while (!(st = sh_lex(fd, g_toks, &it, &ln)))
		{
			sh_eval(fd, g_toks, &ln);
			ft_deqclean(g_toks, (t_dtor)ft_sdsdtor);
		}
		if (st < 0)
			break ;
	}
	sh_varunscope();
	sh_poolunscope();
	rl_finalize(fd);
	return (st < 0 ? (g_shstatus = EXIT_FAILURE) : g_shstatus);
}

int					sh_exit(int exitno, char const *fmt, ...)
{
	va_list	ap;

	if (g_shfd >= 0)
		rl_finalize(g_shfd);
	rl_dtor();
	sh_envdtor();
	sh_evaldtor();
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
