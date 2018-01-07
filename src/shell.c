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

#include <sys/signal.h>

#include "msh/shell.h"

t_bool				g_shinteract = 0;
pid_t				g_shpgid;
TTY					g_shmode;
static t_deq		g_stack_toks = { NULL, sizeof(t_tok), 0, 0, 0 };
static t_deq		*g_toks = &g_stack_toks;
static size_t		g_toks_max = 0;

static inline void	sh_init(int fd)
{
	if (!(g_shinteract = (t_bool)isatty(fd)))
		return ;
	else
	{
		while (tcgetpgrp(fd) != (g_shpgid = getpgrp()))
			kill(-g_shpgid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		g_shpgid = getpid();
		if (setpgid(g_shpgid, g_shpgid) < 0)
		{
			ft_putl(2, "21sh: Couldn't put the shell in its own process group");
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(fd, g_shpgid);
		tcgetattr(fd, &g_shmode);
	}
}

static inline void	sh_finalize(int fd)
{
	sh_readfinalize(fd);
}

inline int			sh_launch(int fd)
{
	char	*ln;
	int		st;
	t_tok	*tok;

	st = EXIT_SUCCESS;
	sh_init(fd);
	tok = alloca(sizeof(t_tok));
	while ((ln = sh_readln(STDIN_FILENO, "$> ")))
	{
		if (!ft_strcmp("exit\n", ln))
			break ;
		st = sh_tokenize(STDIN_FILENO, g_toks, ln);
		while (ft_deqsht(g_toks, tok))
		{
			ft_putf(1, "tok[id='%d',val[%d]='", tok->id, tok->len);
			ft_write(1, tok->val, tok->len);
			ft_puts(1, "']\n");
		}
		g_toks_max = ft_u64max(g_toks_max, g_toks->len);
	}
	sh_finalize(fd);
	return (st);
}

int					sh_exit(int exitno, char const *fmt, ...)
{
	va_list	ap;

	g_toks->len = g_toks_max;
	g_toks->cur = 0;
	ft_deqdtor(g_toks, (t_dtor)sh_tokdtor);
	if (fmt)
	{
		va_start(ap, fmt);
		ft_vputf(2, fmt, ap);
		va_end(ap);
	}
	exit(exitno);
}
