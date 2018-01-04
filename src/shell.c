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

static t_deq		g_stack_toks = { NULL, sizeof(t_tok), 0, 0, 0 };
static t_deq		*g_toks = &g_stack_toks;
static size_t		g_toks_max = 0;

static inline pid_t	sh_init(int fd)
{
	pid_t	pid;

	if (!isatty(fd))
		return (-1);
	else
	{
		while (tcgetpgrp(fd) != (pid = getpgrp()))
			kill(-pid, SIGTTIN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGCHLD, SIG_IGN);
		pid = getpid();
		if (setpgid(pid, pid) < 0)
		{
			ft_putl(2, "21sh: Couldn't put the shell in its own process group");
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(fd, pid);
		return (pid);
	}
}

static inline void	sh_finalize(int fd)
{
	sh_readfinalize(fd);
}

inline int			sh_process(int fd)
{
	char	*ln;
	pid_t	pid;
	int		st;
	t_tok	*tok;

	st = EXIT_SUCCESS;
	pid = sh_init(fd);
	(void)pid;
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
