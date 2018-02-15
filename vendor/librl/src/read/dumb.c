/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read/dumb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../read.h"

inline t_bool	rl_isdumb(void)
{
	static int8_t	isdumb = -1;
	char			*term;

	if (isdumb == -1)
		if ((term = getenv("TERM")) && !ft_strcmp("dumb", term))
			isdumb = 1;
		else
			isdumb = 0;
	return ((t_bool)isdumb);
}
