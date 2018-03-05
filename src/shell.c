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

#include "ush.h"

static t_scope		g_lvls[SHLVL_MAX];
t_scope				*g_sh;
uint8_t				g_shlvl;
int					g_shfd = -1;

inline uint8_t		sh_scope(void)
{
	if (g_shlvl == SHLVL_MAX)
	{
		sh_err("Too many recursion level\n");
		return (0);
	}
	if (g_shlvl == 0)
		ft_bzero(g_lvls, sizeof(t_scope) * SHLVL_MAX);
	g_sh = g_lvls + g_shlvl++;
	if (g_shlvl > 1)
	{
		ft_memcpy(g_sh, g_lvls + g_shlvl - 2, sizeof(t_scope));
		g_sh->prev = g_lvls + g_shlvl - 2;
	}
	ft_mapctor(&g_sh->funcs, g_strhash, sizeof(char *), sizeof(t_func));
	return (g_shlvl);
}

inline uint8_t		sh_unscope(void)
{
	uint32_t	it;
	t_scope		*sh;

	if (g_shlvl == 0)
		sh_exit(EXIT_FAILURE, "Already at minimum shell level\n");
	sh = g_sh;
	if (--g_shlvl > 0 && !g_sh->child)
	{
		g_sh = g_lvls + g_shlvl - 1;
		it = 0;
		while (it < sh->funcs.cap)
		{
			if (BUCKET_ISPOPULATED(sh->funcs.bucks, it))
			{
				sh_funcset(((char **)sh->funcs.keys)[it],
					&((t_func *)sh->funcs.vals)[it].body,
					((t_func *)sh->funcs.vals)[it].ln);
				ft_bzero(&((t_func *)sh->funcs.vals)[it].body, sizeof(t_deq));
			}
			++it;
		}
	}
	ft_mapdtor(&sh->funcs, (t_dtor)ft_pfree, (t_dtor)sh_funcdtor);
	return (g_shlvl);
}

static inline void	sh_init(int fd)
{
	char	*home;
	char	buf[PATH_MAX];

	sh_biregister();
	ps_init(fd, sh_err, sh_exit);
	g_sh->pid = getpgrp();
	if (!(g_sh->tty = (t_bool)isatty(fd)))
		return ;
	rl_complete(sh_complete);
	if ((home = sh_getenv("HOME")) &&
		rl_histload(ft_pathcat(ft_strcpy(buf, home), ".ushst")) < 0)
		sh_exit(EXIT_FAILURE, "The history file `~/.ushst' seems corrupted\n");
	while (tcgetpgrp(fd) != g_sh->pid)
		kill(-g_sh->pid, SIGTTIN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	g_sh->pid = getpid();
	setpgid(g_sh->pid, g_sh->pid);
	tcsetpgrp(fd, g_sh->pid);
}

inline int			sh_run(int fd, char *ln)
{
	char	*it;
	int		st;
	char	buf[PATH_MAX];
	char	*prompt;

	sh_init(fd);
	prompt = !g_sh->status ?" \033[32m❯\033[0m " : " \033[31m❯\033[0m ";
	while (!(st = rl_getline(fd, sh_prompt(prompt, buf), &ln)))
	{
		it = ln;
		st = sh_lex(fd, &it, &ln, sh_eval);
		if (st < 0 || (!g_sh->tty && st == OUF))
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
	rl_dtor();
	ps_dtor();
	sh_envdtor();
	sh_vardtor();
	sh_unscope();
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
