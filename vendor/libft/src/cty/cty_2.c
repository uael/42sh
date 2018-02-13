/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cty_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 11:11:30 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cty.h"

inline int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

inline int	ft_isspace(int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

inline int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

inline int	ft_tolower(int c)
{
	return (ft_isupper(c) ? c ^ 0x20 : c);
}

inline int	ft_toupper(int c)
{
	return (ft_islower(c) ? c ^ 0x20 : c);
}
