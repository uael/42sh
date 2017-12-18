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

inline void		ft_bufgrow(void *buf_ptr, size_t sz, size_t n, size_t isz)
{
	size_t cap;
	size_t req;
	size_t cur;

	if (!sz)
		*(void **)buf_ptr = ft_malloc(ft_u64max(32, pow2_next(n * isz)));
	else
	{
		cur = sz * isz;
		req = cur + (n * isz);
		if (ft_u64max(32, pow2_next(cur)) < (cap = pow2_next(req)))
			*(void **)buf_ptr = ft_realloc(*(void **)buf_ptr, cur, cap);
	}
}

inline void		*ft_bufpush(void *buf_ptr, size_t *sz, size_t n, size_t isz)
{
	void *it;

	ft_bufgrow(buf_ptr, *sz, n, isz);
	it = (char *)*(void **)buf_ptr + (*sz * isz);
	*sz += n;
	return (it);
}

inline size_t	ft_bufshift(void *buf, size_t *sz, size_t n, size_t isz)
{
	if (!*sz)
		return (0);
	if (n > *sz)
		n = *sz;
	if (*sz -= n)
		ft_memmove(buf, (char *)buf + (n * isz), *sz * isz);
	return (n);
}
