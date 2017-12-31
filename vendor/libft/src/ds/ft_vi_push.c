/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_push(t_vi8 *self)
{
	return (ft_vi8_pushn(self, 1));
}

inline int16_t	*ft_vi16_push(t_vi16 *self)
{
	return (ft_vi16_pushn(self, 1));
}

inline int32_t	*ft_vi32_push(t_vi32 *self)
{
	return (ft_vi32_pushn(self, 1));
}

inline int64_t	*ft_vi64_push(t_vi64 *self)
{
	return (ft_vi64_pushn(self, 1));
}

inline char		**ft_vstr_push(t_vstr *self)
{
	return (ft_vstr_pushn(self, 1));
}
