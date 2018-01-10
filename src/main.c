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

#include "msh.h"

static int	g_fd = -1;

static int	exhdl(int rcode, void *arg)
{
	if (!errno)
		return (rcode);
	if (arg)
		ft_putf(2, COLOR_BRED"21sh: "COLOR_RESET"%s: %e\n", arg, errno);
	else
		ft_putf(2, COLOR_BRED"21sh: "COLOR_RESET"%e\n", errno);
	if (errno == ENOMEM || errno == EIO || errno == EINVAL || errno > ELAST)
	{
		if (g_fd >= 0)
			sh_readfinalize(g_fd);
		exit(EXIT_FAILURE);
	}
	errno = 0;
	return (rcode);
}

int			main(int ac, char **av, char **envv)
{
	int		st;

	st = EXIT_SUCCESS;
	ft_exbind(0, ft_exhdl(exhdl, NULL), NULL);
	sh_envinit(envv);
	if (ac == 1)
		return (sh_exit(sh_launch(g_fd = STDIN_FILENO), NULL));
	else
		while (*++av)
		{
			ft_exbind(0, ft_exhdl(exhdl, *av), NULL);
			if ((g_fd = open(*av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
				THROW(WUT);
			else
				st = sh_launch(g_fd);
		}
	return (sh_exit(st, NULL));
}
