/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_put(t_vi8 *self, size_t idx)
{
	return (ft_vi8_putn(self, idx, 1));
}

inline int16_t	*ft_vi16_put(t_vi16 *self, size_t idx)
{
	return (ft_vi16_putn(self, idx, 1));
}

inline int32_t	*ft_vi32_put(t_vi32 *self, size_t idx)
{
	return (ft_vi32_putn(self, idx, 1));
}

inline int64_t	*ft_vi64_put(t_vi64 *self, size_t idx)
{
	return (ft_vi64_putn(self, idx, 1));
}

inline char		**ft_vstr_put(t_vstr *self, size_t idx)
{
	return (ft_vstr_putn(self, idx, 1));
}
