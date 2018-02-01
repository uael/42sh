/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/bi/read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush.h"

struct termios	sh_bireadterm(int init)
{
	static struct termios	term;

	if (init)
		tcgetattr(0, &term);
	return (term);
}

int				sh_bireadterminit(t_read *data)
{
	struct termios	term;

	term = sh_bireadterm(1);
	if (!(data->flag & BI_READINTER))
		return (YEP);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VTIME] = data->timeout * 10;
	term.c_cc[VMIN] = data->timeout ? 0 : 1;
	term.c_cc[VEOL] = data->delim;
	if (tcsetattr(0, TCSANOW, &term) < 0)
	{
		ft_putf(STDERR_FILENO, "tcsetattr(): %e", errno);
		return (WUT);
	}
	return (YEP);
}

int				sh_bireadexit(t_read *data)
{
	struct termios	term;

	ft_pfree((void **)&data->input);
	term = sh_bireadterm(0);
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (-1);
	return (0);
}