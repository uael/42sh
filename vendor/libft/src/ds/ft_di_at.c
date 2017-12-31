/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_at(t_di8 *self, size_t idx)
{
	return (ft_di8_begin(self) + idx);
}

inline int16_t	*ft_di16_at(t_di16 *self, size_t idx)
{
	return (ft_di16_begin(self) + idx);
}

inline int32_t	*ft_di32_at(t_di32 *self, size_t idx)
{
	return (ft_di32_begin(self) + idx);
}

inline int64_t	*ft_di64_at(t_di64 *self, size_t idx)
{
	return (ft_di64_begin(self) + idx);
}

inline char		**ft_dqstr_at(t_dqstr *self, size_t idx)
{
	return (ft_dqstr_begin(self) + idx);
}
