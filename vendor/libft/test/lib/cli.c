/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int			main(void)
{
	int		ok;
	int		nok;
	t_test	*it;

	ft_write(STDOUT_FILENO, SNS("test: setup.........."));
	if (setup())
		return ((int)(NOK & 0) + EXIT_FAILURE);
	OK;
	ok = 0;
	nok = 0;
	it = g_tests - 1;
	while (it && (++it)->name)
		if (it->cb)
		{
			ft_write(STDOUT_FILENO, SNS("test: "));
			ft_write(STDOUT_FILENO, it->name, ft_strlen(it->name));
			ft_putr(STDOUT_FILENO, '.', 15 - ft_strlen(it->name));
			(void)(it->cb() ? (++nok) : (++ok && OK));
		}
	ft_write(STDOUT_FILENO, SNS("test: teardown......."));
	if (teardown())
		return ((int)(NOK & 0) + EXIT_FAILURE);
	OK;
	return (EXIT_SUCCESS);
}
