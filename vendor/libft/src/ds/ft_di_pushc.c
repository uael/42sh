/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_pushc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_pushc(t_di8 *self, int8_t item)
{
	int8_t *it;

	if (!(it = ft_di8_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int16_t	*ft_di16_pushc(t_di16 *self, int16_t item)
{
	int16_t *it;

	if (!(it = ft_di16_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int32_t	*ft_di32_pushc(t_di32 *self, int32_t item)
{
	int32_t *it;

	if (!(it = ft_di32_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int64_t	*ft_di64_pushc(t_di64 *self, int64_t item)
{
	int64_t *it;

	if (!(it = ft_di64_push(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline char		**ft_dqstr_pushc(t_dqstr *self, char *item)
{
	char **it;

	if (!(it = ft_dqstr_push(self)))
		return (NULL);
	*it = item;
	return (it);
}
