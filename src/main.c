/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

#include "msh.h"

int	sh_av(t_deq *toks, char **av)
{
	int		fd;
	char	*ln;

	while (++*av)
		if ((fd = open(*av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
			THROW(WUT);
		else
			while ((ln = sh_readln(fd, "$> ")))
			{
				sh_tokenize(fd, toks, ln);
				ft_puts(STDOUT_FILENO, sh_histln()->buf);
			}
	return (YEP);
}

pid_t shell_pgid;

int	main(int ac, char **av)
{
	t_deq	*toks;
	int		st;
	char	*ln;
	t_tok	*tok;

	st = EXIT_SUCCESS;
	tok = alloca(sizeof(t_tok));
	ft_deqctor(toks = alloca(sizeof(t_deq)), sizeof(t_tok));
	if (ac > 1)
		st = sh_av(toks, av);
	else
	{
		if (isatty(STDIN_FILENO))
		{
			/* Loop until we are in the foreground.  */
			while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
				kill(-shell_pgid, SIGTTIN);
			/* Ignore interactive and job-control signals.  */
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGTSTP, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			signal(SIGTTOU, SIG_IGN);
			signal(SIGCHLD, SIG_IGN);
			/* Put ourselves in our own process group.  */
			shell_pgid = getpid();
			if (setpgid(shell_pgid, shell_pgid) < 0)
			{
				perror("Couldn't put the shell in its own process group");
				exit(1);
			}
			/* Grab control of the terminal.  */
			tcsetpgrp(STDIN_FILENO, shell_pgid);
		}
		while ((ln = sh_readln(STDIN_FILENO, "$> ")))
		{
			if (!ft_strcmp("exit\n", ln))
				break ;
			st = sh_tokenize(STDIN_FILENO, toks, ln);
			while (ft_deqsht(toks, tok))
			{
				ft_putf(1, "tok[id='%d',val[%d]='", tok->id, tok->len);
				ft_write(1, tok->val, tok->len);
				ft_puts(1, "']\n");
			}
		}
	}
	return (st);
}
