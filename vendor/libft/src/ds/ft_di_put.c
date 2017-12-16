/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_put(t_di8 *self, size_t idx)
{
	return (ft_di8_putn(self, idx, 1));
}

inline int16_t	*ft_di16_put(t_di16 *self, size_t idx)
{
	return (ft_di16_putn(self, idx, 1));
}

inline int32_t	*ft_di32_put(t_di32 *self, size_t idx)
{
	return (ft_di32_putn(self, idx, 1));
}

inline int64_t	*ft_di64_put(t_di64 *self, size_t idx)
{
	return (ft_di64_putn(self, idx, 1));
}

inline char		**ft_dqstr_put(t_dqstr *self, size_t idx)
{
	return (ft_dqstr_putn(self, idx, 1));
}
