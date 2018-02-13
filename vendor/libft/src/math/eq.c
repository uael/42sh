/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 17:19:30 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"

inline t_bool	ft_ieq(int a, int b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_ueq(unsigned int a, unsigned int b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_leq(long a, long b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_uleq(unsigned long a, unsigned long b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_lleq(long long int a, long long int b)
{
	return ((t_bool)(a == b));
}
