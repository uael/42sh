/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_end(t_vi8 *self)
{
	return (self->buf + self->len);
}

inline int16_t	*ft_vi16_end(t_vi16 *self)
{
	return (self->buf + self->len);
}

inline int32_t	*ft_vi32_end(t_vi32 *self)
{
	return (self->buf + self->len);
}

inline int64_t	*ft_vi64_end(t_vi64 *self)
{
	return (self->buf + self->len);
}

inline char		**ft_vstr_end(t_vstr *self)
{
	return (self->buf + self->len);
}
