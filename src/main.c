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

int	main(int ac, char **av)
{
	int		st;
	int		fd;

	st = EXIT_SUCCESS;
	if (ac == 1)
		return (sh_exit(sh_process(STDIN_FILENO), NULL));
	else
		while (++*av)
			if ((fd = open(*av, O_RDONLY, S_IRGRP | S_IRUSR)) < 0)
				THROW(WUT);
			else
				st = sh_process(fd);
	return (sh_exit(st, NULL));
}
