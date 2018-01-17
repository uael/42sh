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

#include "ush/bi.h"

static void		echo_out(char **str, int pos)
{
	int		starts_with;
	int		ends_with;
	int		str_len;

	starts_with = IS_QUOTE(str[pos][0]);
	str_len = (int)ft_strlen(str[pos]);
	ends_with = IS_QUOTE(str[pos][str_len - 1]);
	if (ends_with && starts_with)
		ft_write(1, str[pos] + 1, ft_strlen(str[pos]) - 1);
	else if (ends_with)
		ft_write(1, str[pos] + 1, ft_strlen(str[pos]) - 1);
	else if (starts_with)
		ft_puts(1, str[pos] + 1);
	else
		ft_puts(1, str[pos]);
	if (str[pos + 1])
		ft_putc(1, ' ');
}

int				bi_echo(char **argv)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!argv[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (argv[0][0] == '-' && argv[0][1] == 'n' && argv[0][2] == '\0')
		n_flag = 1;
	i = -1;
	if (n_flag)
		++i;
	while (argv[++i])
	{
		echo_out(argv, i);
		if (!argv[i + 1] && !n_flag)
			ft_putc(1, '\n');
	}
	return (1);
}