/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_begin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_begin(t_vi8 *self)
{
	return (self->buf);
}

inline int16_t	*ft_vi16_begin(t_vi16 *self)
{
	return (self->buf);
}

inline int32_t	*ft_vi32_begin(t_vi32 *self)
{
	return (self->buf);
}

inline int64_t	*ft_vi64_begin(t_vi64 *self)
{
	return (self->buf);
}

inline char		**ft_vstr_begin(t_vstr *self)
{
	return (self->buf);
}
