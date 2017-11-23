/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_unshiftnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_unshiftnc(t_di8 *self, int8_t const *items, size_t n)
{
	int8_t *it;

	if (!(it = ft_di8_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int8_t));
	return (it);
}

inline int16_t	*ft_di16_unshiftnc(t_di16 *self, int16_t const *items, size_t n)
{
	int16_t *it;

	if (!(it = ft_di16_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int16_t));
	return (it);
}

inline int32_t	*ft_di32_unshiftnc(t_di32 *self, int32_t const *items, size_t n)
{
	int32_t *it;

	if (!(it = ft_di32_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int32_t));
	return (it);
}

inline int64_t	*ft_di64_unshiftnc(t_di64 *self, int64_t const *items, size_t n)
{
	int64_t *it;

	if (!(it = ft_di64_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(int64_t));
	return (it);
}

inline char		**ft_dqstr_unshiftnc(t_dqstr *self, char const **items, size_t n)
{
	char **it;

	if (!(it = ft_dqstr_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(char *));
	return (it);
}
