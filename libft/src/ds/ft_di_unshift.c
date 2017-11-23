/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_unshift.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_unshift(t_di8 *self)
{
	return (ft_di8_unshiftn(self, 1));
}

inline int16_t	*ft_di16_unshift(t_di16 *self)
{
	return (ft_di16_unshiftn(self, 1));
}

inline int32_t	*ft_di32_unshift(t_di32 *self)
{
	return (ft_di32_unshiftn(self, 1));
}

inline char		**ft_dqstr_unshift(t_dqstr *self)
{
	return (ft_dqstr_unshiftn(self, 1));
}
