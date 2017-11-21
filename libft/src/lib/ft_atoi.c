/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:57:36 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"

inline int64_t	ft_atoi(char const *str)
{
	int64_t	result;
	char	sign;

	result = 0;
	while (ft_isspace(*str))
		++str;
	if ((sign = *str) == '+' || sign == '-')
		++str;
	while (ft_isdigit(*str))
		result = result * 10 + *str++ - '0';
	return ((int64_t)(sign == '-' ? -result : result));
}

inline double	ft_atod(char const *str)
{
	double	d;
	double	m;
	t_bool	floating;
	char	sign;

	floating = 0;
	d = 0.0;
	m = 1;
	while (ft_isspace(*str))
		++str;
	if ((sign = *str) == '+' || sign == '-')
		++str;
	while (*str)
	{
		if (*str == '.')
			floating = 1;
		else if (ft_isdigit(*str))
		{
			if (floating)
				m /= 10.0f;
			d = d * 10.0f + (float)*str - '0';
		}
		++str;
	}
	return (sign == '-' ? -d : d);
}
