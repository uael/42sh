/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_putnc(t_di8 *self, size_t i, int8_t const *b, size_t n)
{
	int8_t *it;

	if (!(it = ft_di8_putn(self, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int8_t));
	return (it);
}

inline int16_t	*ft_di16_putnc(t_di16 *s, size_t i, int16_t const *b, size_t n)
{
	int16_t *it;

	if (!(it = ft_di16_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int16_t));
	return (it);
}

inline int32_t	*ft_di32_putnc(t_di32 *s, size_t i, int32_t const *b, size_t n)
{
	int32_t *it;

	if (!(it = ft_di32_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int32_t));
	return (it);
}

inline int64_t	*ft_di64_putnc(t_di64 *s, size_t i, int64_t const *b, size_t n)
{
	int64_t *it;

	if (!(it = ft_di64_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}

inline char		**ft_dqstr_putnc(t_dqstr *s, size_t i, char const **b, size_t n)
{
	char **it;

	if (!(it = ft_dqstr_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}
