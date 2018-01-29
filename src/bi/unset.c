/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

static char const	*g_usage = "usage: unset [NAME ...]\n"
"\tThe unset builtin command is used to unset values and attributes\n"
"\tof shell variables.\n";

static int			unsetexhdl(int rcode, void *arg)
{
	if (!errno || errno == EBADF || errno == EIO)
		return (rcode);
	if (arg)
		ft_putf(STDERR_FILENO, COLOR_BRED"unset: "COLOR_RESET"%s: %e\n",
			arg, errno);
	else
		ft_putf(STDERR_FILENO, COLOR_BRED"unset: "COLOR_RESET"%e\n", errno);
	if (errno == ENOARG)
		ft_puts(STDERR_FILENO, g_usage);
	if (errno == ENOMEM)
		sh_exit(EXIT_FAILURE, NULL);
	errno = 0;
	return (rcode);
}

inline int			sh_biunset(int ac, char **av)
{
	ft_exbind(EXALL, ft_exhdl(unsetexhdl, NULL), NULL);
	if (ac == 1)
		return (ENO_THROW(EXIT_FAILURE, ENOARG));
	while (*++av)
	{
		ft_exbind(EXALL, ft_exhdl(unsetexhdl, *av), NULL);
		if (sh_isname(*av) && !ft_strchr(*av, '=') && sh_varget(*av))
			sh_varset(*av, NULL);
	}
	return (EXIT_SUCCESS);
}
