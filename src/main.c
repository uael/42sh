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

#include "ush.h"

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
	if (ac == 1)
		return (sh_exit(sh_run(g_shfd = STDIN_FILENO), NULL));
	else
		while (*++av)
		{
			ft_exbind(0, ft_exhdl(exhdl, *av), NULL);
			if ((g_shfd = open(*av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
				THROW(WUT);
			else
				st = sh_run(g_shfd);
		}
	return (sh_exit(st, NULL));
}
