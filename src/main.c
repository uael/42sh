/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/26 03:08:45 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

static int	usage(char const *exe_name, int error)
{
	int fd;

	fd = error ? 2 : 1;
	ft_putf(fd,
		"Usage: %s [option] [script-file] [script arguments...]\n"
		"ush options:\n"
		"\t--help: this *useful* help message!\n"
		"ush keymap:\n"
		"\t<ctrl+A|home>: Go to begin of line.\n"
		"\t<ctrl+E|end>: Go to end of line.\n"
		"\t<ctrl+V>: Enter visual mode.\n"
		"\t<ctrl+Y>: Yank in visual mode.\n"
		"\t<ctrl+P>: Paste.\n"
		"\t<ctrl+D>: Exit or delete in visual mode.\n"
		"\t<ctrl+C>: Cancel line edition.\n"
		"\t<ctrl+L>: Clear the screen.\n"
		"\t<shift+[left|right]>: Move per word.\n"
		"\t<shift+[up|down]>: Move per line.\n"
		"\t<up>: Go up in the history.\n"
		"\t<down>: Go down in the history.\n"
		"\t!!: Retype the last command.\n"
		"\t!n: Retype the n command from the begin of history.\n"
		"\t!-n: Retype the -n command from the last command.\n"
		"\t!name: Search for a command beginning with name.\n", exe_name);
	return (error ? EXIT_FAILURE : EXIT_SUCCESS);
}

static int	exhdl(int rcode, void *arg)
{
	if (!errno || errno == EBADF)
		return (rcode);
	if (errno == EIO)
		sh_exit(EXIT_FAILURE, NULL);
	if (arg)
		sh_err("%s: %e\n", arg, errno);
	else
		sh_err("%e\n", errno);
	if (errno == ENOMEM || errno == EINVAL || errno > ELAST)
		sh_exit(EXIT_FAILURE, NULL);
	errno = 0;
	return (rcode);
}

int			main(int ac, char **av, char **envv)
{
	int		st;

	st = EXIT_SUCCESS;
	ft_exbind(EXALL, ft_exhdl(exhdl, NULL), NULL);
	sh_envinit(envv);
	sh_scope();
	g_sh->ac = ac;
	g_sh->av = av;
	if (ac == 1)
		return (sh_exit(sh_run(g_shfd = STDIN_FILENO, NULL), NULL));
	else if (!ft_strcmp(*(av + 1), "--help"))
		return (usage(*av, YEP));
	else
	{
		--g_sh->ac;
		++g_sh->av;
		ft_exbind(0, ft_exhdl(exhdl, *g_sh->av), NULL);
		if ((g_shfd = open(*g_sh->av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
			ft_throw(WUT, FT_DBG);
		else if (!access(*av, X_OK) && !ft_strendw(*g_sh->av, ".sh"))
			return (sh_exit(EXIT_FAILURE, "Cannot execute binary file\n"));
		else
			st = sh_run(g_shfd, NULL);
	}
	return (sh_exit(st, NULL));
}
