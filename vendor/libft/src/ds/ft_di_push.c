/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_push(t_di8 *self)
{
	return (ft_di8_pushn(self, 1));
}

inline int16_t	*ft_di16_push(t_di16 *self)
{
	return (ft_di16_pushn(self, 1));
}

inline int32_t	*ft_di32_push(t_di32 *self)
{
	return (ft_di32_pushn(self, 1));
}

inline int64_t	*ft_di64_push(t_di64 *self)
{
	return (ft_di64_pushn(self, 1));
}

inline char		**ft_dqstr_push(t_dqstr *self)
{
	return (ft_dqstr_pushn(self, 1));
}
