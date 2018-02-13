/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 11:10:49 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cty.h"

inline int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

inline int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

inline int	ft_isascii(int c)
{
	return (c >= 0 && c < 128);
}

inline int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

inline int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
