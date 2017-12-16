/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline uint8_t	*ft_du8_putnc(t_du8 *self, size_t i, uint8_t const *b, size_t n)
{
	uint8_t *it;

	if (!(it = ft_du8_putn(self, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int8_t));
	return (it);
}

inline uint16_t	*ft_du16_putnc(t_du16 *s, size_t i, uint16_t const *b, size_t n)
{
	uint16_t *it;

	if (!(it = ft_du16_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int16_t));
	return (it);
}

inline uint32_t	*ft_du32_putnc(t_du32 *s, size_t i, uint32_t const *b, size_t n)
{
	uint32_t *it;

	if (!(it = ft_du32_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int32_t));
	return (it);
}

inline uint64_t	*ft_du64_putnc(t_du64 *s, size_t i, uint64_t const *b, size_t n)
{
	uint64_t *it;

	if (!(it = ft_du64_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}

inline void		*ft_deq_putnc(t_deq *s, size_t i, void const *b, size_t n)
{
	uint64_t *it;

	if (!(it = ft_deq_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * s->isz);
	return (it);
}
