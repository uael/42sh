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
#include "ush/eval.h"

#define SH_PROMPT() (g_sh->status==0?" \033[32m❯\033[0m ":" \033[31m❯\033[0m ")

static t_deq		g_stack_toks = { NULL, sizeof(t_tok), 0, 0, 0 };
static t_deq		*g_toks = &g_stack_toks;
static t_scope		g_lvls[SHLVL_MAX] =
{
	{ 0, NULL, 0, 0, 0, 0 }
};
t_scope				*g_sh;
uint8_t				g_shlvl;
TTY					g_shmode;
int					g_shfd = -1;

inline uint8_t		sh_scope(void)
{
	if (g_shlvl == SHLVL_MAX)
	{
		sh_err("Too many shell level\n");
		sh_exit(EXIT_FAILURE, NULL);
	}
	g_sh = g_lvls + g_shlvl++;
	return (g_shlvl);
}

inline uint8_t		sh_unscope(void)
{
	if (g_shlvl == 1)
	{
		sh_err("Already at minimum shell level\n");
		rl_dtor();
		sh_exit(EXIT_FAILURE, NULL);
	}
	g_sh = g_lvls + --g_shlvl;
	return (g_shlvl);
}

static inline void	sh_init(int fd)
{
	char	*home;
	char	buf[PATH_MAX];

	g_sh->pid = getpgrp();
	if (!(g_sh->tty = (t_bool)isatty(fd)))
		return ;
	while (tcgetpgrp(fd) != g_sh->pid)
		kill(-g_sh->pid, SIGTTIN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	g_sh->pid = getpid();
	if (setpgid(g_sh->pid, g_sh->pid) < 0)
		sh_exit(EXIT_FAILURE, "Couldn't put the shell in its own process "
			"group");
	tcsetpgrp(fd, g_sh->pid);
	tcgetattr(fd, &g_shmode);
	rl_hook(sh_poolnotify);
	rl_complete(sh_complete);
	if ((home = sh_getenv("HOME")))
		rl_histload(ft_pathcat(ft_strcpy(buf, home), ".ushst"));
}

inline int			sh_run(int fd, char *ln)
{
	char	*it;
	int		st;
	char	buf[PATH_MAX];

	sh_init(fd);
	while (!(st = rl_getline(fd, sh_prompt(SH_PROMPT(), buf), &ln)))
	{
		it = ln;
		g_toks->len = 0;
		g_toks->cur = 0;
		while (!(st = sh_tokenize(fd, &it, &ln, sh_eval)))
			;
		if (st < 0 || ((st == OUF ? (g_sh->status = 1) : 0) && !g_sh->status))
			break ;
	}
	rl_finalize(fd);
	return (st < 0 ? (g_sh->status = EXIT_FAILURE) : g_sh->status);
}

int					sh_exit(int exitno, char const *fmt, ...)
{
	va_list	ap;
	char	*home;
	char	buf[PATH_MAX];

	if (g_sh->tty && (home = sh_getenv("HOME")))
		rl_histsave(ft_pathcat(ft_strcpy(buf, home), ".ushst"));
	if (g_shfd >= 0)
		rl_finalize(g_shfd);
	g_toks->cur = 0;
	ft_deqdtor(g_toks, (t_dtor)sh_tokdtor);
	rl_dtor();
	sh_envdtor();
	sh_vardtor();
	sh_evaldtor();
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
