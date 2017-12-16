/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_unshiftc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_unshiftc(t_vi8 *self, int8_t item)
{
	int8_t *it;

	if (!(it = ft_vi8_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int16_t	*ft_vi16_unshiftc(t_vi16 *self, int16_t item)
{
	int16_t *it;

	if (!(it = ft_vi16_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int32_t	*ft_vi32_unshiftc(t_vi32 *self, int32_t item)
{
	int32_t *it;

	if (!(it = ft_vi32_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline int64_t	*ft_vi64_unshiftc(t_vi64 *self, int64_t item)
{
	int64_t *it;

	if (!(it = ft_vi64_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}

inline char		**ft_vstr_unshiftc(t_vstr *self, char *item)
{
	char **it;

	if (!(it = ft_vstr_unshift(self)))
		return (NULL);
	*it = item;
	return (it);
}
