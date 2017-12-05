/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:50:09 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline t_sz	ft_omstream_putc(t_omstream *self, char c)
{
	return (ft_omstream_write(self, &c, 1));
}

inline t_sz	ft_omstream_puts(t_omstream *self, char const *s)
{
	return (ft_omstream_write(self, s, ft_strlen(s)));
}
