/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ofstream_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:50:09 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/ofstream.h"

inline t_sz	ft_ofstream_putc(t_ofstream *self, char c)
{
	return (ft_ofstream_write(self, &c, 1));
}

inline t_sz	ft_ofstream_puts(t_ofstream *self, char const *s)
{
	return (ft_ofstream_write(self, s, ft_strlen(s)));
}
