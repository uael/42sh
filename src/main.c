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

static int sh_help(char const *exe_name, int error)
{
	int fd;

	fd = error ? 2 : 1;
	write(fd, "Usage: ", 7);
	write(fd, exe_name, ft_strlen(exe_name));
	write(fd, " [option] [script-file...]\n" \
		"ush options:\n" \
		"\t--help: this *useful* help message!\n", 77);
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
		return (sh_help(*av, NOP));
	else
	{
		--g_sh->ac;
		++g_sh->av;
		ft_exbind(0, ft_exhdl(exhdl, *g_sh->av), NULL);
		if ((g_shfd = open(*g_sh->av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
			THROW(WUT);
		else if (!access(*av, X_OK) && !ft_strendw(*g_sh->av, ".sh"))
			return (sh_exit(EXIT_FAILURE, "Cannot execute binary file\n"));
		else
			st = sh_run(g_shfd, NULL);
	}
	return (sh_exit(st, NULL));
}
