/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imstream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/imstream.h"

inline void	ft_imstream_open(t_imstream *self, char const *str)
{
	FT_INIT(self, t_imstream);
	self->buf = str;
	self->len = ft_strlen(str);
}

inline void	ft_imstream_nopen(t_imstream *self, char const *str, size_t n)
{
	FT_INIT(self, t_imstream);
	self->buf = str;
	self->len = n;
}
