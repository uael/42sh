/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 17:19:30 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/math.h"
#include "libft/str.h"

inline t_bool	ft_ulleq(unsigned long long int a, unsigned long long int b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_szeq(ssize_t a, ssize_t b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_uszeq(size_t a, size_t b)
{
	return ((t_bool)(a == b));
}

inline t_bool	ft_streq(char const *a, char const *b)
{
	return ((t_bool)(a == b || !ft_strcmp(a, b)));
}
