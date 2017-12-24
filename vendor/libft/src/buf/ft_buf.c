/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:23 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 12:30:38 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/buf.h"

inline void		*ft_bufaver(void const *buf, size_t n, size_t len, size_t isz)
{
	if (n > pow2_next(len))
		return (ft_realloc(buf, len * isz, pow2_next(n) * isz));
	return ((void *)buf);
}

inline void		*ft_bufgrow(void const *buf, size_t n, size_t len, size_t isz)
{
	if ((len + n) > pow2_next(len))
		return (ft_realloc(buf, len * isz, pow2_next(len + n) * isz));
	return ((void *)buf);
}

inline void		*ft_bufpush(void const *buf, size_t n, size_t len, size_t isz)
{
	return (ft_bufgrow(buf, n, len, isz));
}

inline size_t	ft_bufshift(void *buf, size_t n, size_t len, size_t isz)
{
	size_t nsz;

	if (!len)
		return (0);
	if (n > len)
		n = len;
	if ((nsz = (len - n)))
		ft_memmove(buf, ft_bufat(buf, n, isz), nsz * isz);
	return (n);
}

inline void		*ft_bufat(void const *buf, size_t i, size_t isz)
{
	return ((char *)buf + (i * isz));
}
