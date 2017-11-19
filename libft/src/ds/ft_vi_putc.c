/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_putc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_putc(t_vi8 *self, size_t idx, int8_t item)
{
	int8_t *it;

	if (!(it = ft_vi8_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int16_t	*ft_vi16_putc(t_vi16 *self, size_t idx, int16_t item)
{
	int16_t *it;

	if (!(it = ft_vi16_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int32_t	*ft_vi32_putc(t_vi32 *self, size_t idx, int32_t item)
{
	int32_t *it;

	if (!(it = ft_vi32_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int64_t	*ft_vi64_putc(t_vi64 *self, size_t idx, int64_t item)
{
	int64_t *it;

	if (!(it = ft_vi64_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline char		**ft_vstr_putc(t_vstr *self, size_t idx, char *item)
{
	char	**it;

	if (!(it = ft_vstr_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}
