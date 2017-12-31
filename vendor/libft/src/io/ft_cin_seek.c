/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cin_seek.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:09:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/istream.h"

inline void		ft_cin_flush(void)
{
	return (ft_istream_flush(g_cin));
}

inline int		ft_cin_rewind(size_t n)
{
	return (ft_istream_rewind(g_cin, n));
}

inline int		ft_cin_forward(size_t n)
{
	return (ft_istream_forward(g_cin, n));
}

inline int		ft_cin_seek(size_t off)
{
	return (ft_istream_seek(g_cin, off));
}

inline size_t	ft_cin_tell(void)
{
	return (ft_istream_tell(g_cin));
}
