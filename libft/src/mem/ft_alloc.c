/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 11:13:39 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mem.h"

#include "libft/ex.h"
#include "libft/str.h"

inline void	*ft_malloc(size_t sz)
{
	void *p;

	if (!(p = malloc(sz)))
		return ((void	*)ft_ex_throw(0));
	return (p);
}

inline void	*ft_calloc(size_t sz)
{
	void *ptr;

	if ((ptr = ft_malloc(sz)))
		ft_memset(ptr, 0, sz);
	return (ptr);
}

inline void	*ft_realloc(void *ptr, size_t psz, size_t sz)
{
	void *p;

	if (!(p = ft_malloc(sz)))
		return (NULL);
	if (!ptr)
		return (p);
	ft_memcpy(p, ptr, psz);
	free(ptr);
	return (p);
}
