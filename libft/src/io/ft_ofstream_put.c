/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ofstream_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 11:20:40 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ofstream.h"

inline ssize_t	ft_ofstream_puts(t_ofstream *self, char const *s)
{
	return (ft_ofstream_write(self, s, ft_strlen(s)));
}

inline int		ft_ofstream_putc(t_ofstream *self, char c)
{
	ssize_t sz;

	return ((sz = ft_ofstream_write(self, &c, 1)) == 1 ? YEP : (int)sz);
}
