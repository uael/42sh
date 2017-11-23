/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cin_read.c                                      :+:      :+:    :+:   */
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
	return (ft_istream_flush(cin));
}

inline t_ret	ft_cin_rewind(size_t n)
{
	return (ft_istream_rewind(cin, n));
}

inline t_ret	ft_cin_forward(size_t n)
{
	return (ft_istream_forward(cin, n));
}

inline t_ret	ft_cin_seek(size_t off)
{
	return (ft_istream_seek(cin, off));
}

inline size_t	ft_cin_tell(void)
{
	return (ft_istream_tell(cin));
}
