/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omstream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 09:51:01 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/omstream.h"

inline void	ft_omstream_open(t_omstream *self)
{
	ft_du8_ctor(self);
}

inline void	ft_omstream_close(t_omstream *self)
{
	ft_du8_dtor(self, NULL);
}
