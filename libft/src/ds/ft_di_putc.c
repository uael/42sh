/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_putc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_putc(t_di8 *self, size_t idx, int8_t item)
{
	int8_t *it;

	if (!(it = ft_di8_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int16_t	*ft_di16_putc(t_di16 *self, size_t idx, int16_t item)
{
	int16_t *it;

	if (!(it = ft_di16_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int32_t	*ft_di32_putc(t_di32 *self, size_t idx, int32_t item)
{
	int32_t *it;

	if (!(it = ft_di32_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline int64_t	*ft_di64_putc(t_di64 *self, size_t idx, int64_t item)
{
	int64_t *it;

	if (!(it = ft_di64_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}

inline char		**ft_dqstr_putc(t_dqstr *self, size_t idx, char *item)
{
	char	**it;

	if (!(it = ft_dqstr_put(self, idx)))
		return (NULL);
	*it = item;
	return (it);
}
