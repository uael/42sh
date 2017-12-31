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
				sh_tokenize(toks, ln);
			}
	return (YEP);
}

int	main(int ac, char **av)
{
	t_deq	*toks;
	int		st;
	char	*ln;

	st = EXIT_SUCCESS;
	ft_deqctor(toks = alloca(sizeof(t_deq)), sizeof(t_tok));
	if (ac > 1)
		st = sh_av(toks, av);
	else
		while ((ln = sh_readln(STDIN_FILENO, "$> ")))
		{
			st = sh_tokenize(toks, ln);
		}
	return (st);
}
