/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cout_seek.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:09:14 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ostream.h"

inline void		ft_cout_flush(void)
{
	return (ft_ostream_flush(g_cout));
}

inline t_st		ft_cout_rewind(size_t n)
{
	return (ft_ostream_rewind(g_cout, n));
}

inline t_st		ft_cout_forward(size_t n)
{
	return (ft_ostream_forward(g_cout, n));
}

inline t_st		ft_cout_seek(size_t off)
{
	return (ft_ostream_seek(g_cout, off));
}

inline size_t	ft_cout_tell(void)
{
	return (ft_ostream_tell(g_cout));
}
