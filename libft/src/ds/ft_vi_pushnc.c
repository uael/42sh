/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_pushnc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_pushnc(t_vi8 *self, int8_t const *items, size_t n)
{
	int8_t *it;

	if (!(it = ft_vi8_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int8_t));
	return (it);
}

inline int16_t	*ft_vi16_pushnc(t_vi16 *self, int16_t const *items, size_t n)
{
	int16_t *it;

	if (!(it = ft_vi16_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int16_t));
	return (it);
}

inline int32_t	*ft_vi32_pushnc(t_vi32 *self, int32_t const *items, size_t n)
{
	int32_t *it;

	if (!(it = ft_vi32_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int32_t));
	return (it);
}

inline int64_t	*ft_vi64_pushnc(t_vi64 *self, int64_t const *items, size_t n)
{
	int64_t *it;

	if (!(it = ft_vi64_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int64_t));
	return (it);
}

inline char		**ft_vstr_pushnc(t_vstr *self, char const **items, size_t n)
{
	char **it;

	if (!(it = ft_vstr_pushn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(char *));
	return (it);
}
