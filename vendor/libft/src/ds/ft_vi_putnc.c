/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_putn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_putnc(t_vi8 *self, size_t i, int8_t const *b, size_t n)
{
	int8_t *it;

	if (!(it = ft_vi8_putn(self, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int8_t));
	return (it);
}

inline int16_t	*ft_vi16_putnc(t_vi16 *s, size_t i, int16_t const *b, size_t n)
{
	int16_t *it;

	if (!(it = ft_vi16_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int16_t));
	return (it);
}

inline int32_t	*ft_vi32_putnc(t_vi32 *s, size_t i, int32_t const *b, size_t n)
{
	int32_t *it;

	if (!(it = ft_vi32_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int32_t));
	return (it);
}

inline int64_t	*ft_vi64_putnc(t_vi64 *s, size_t i, int64_t const *b, size_t n)
{
	int64_t *it;

	if (!(it = ft_vi64_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}

inline char		**ft_vstr_putnc(t_vstr *s, size_t i, char const **b, size_t n)
{
	char **it;

	if (!(it = ft_vstr_putn(s, i, n)))
		return (NULL);
	ft_memcpy(it, b, n * sizeof(int64_t));
	return (it);
}
