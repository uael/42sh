/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline int8_t	*ft_vi8_at(t_vi8 *self, size_t idx)
{
	return (ft_vi8_begin(self) + idx);
}

inline int16_t	*ft_vi16_at(t_vi16 *self, size_t idx)
{
	return (ft_vi16_begin(self) + idx);
}

inline int32_t	*ft_vi32_at(t_vi32 *self, size_t idx)
{
	return (ft_vi32_begin(self) + idx);
}

inline int64_t	*ft_vi64_at(t_vi64 *self, size_t idx)
{
	return (ft_vi64_begin(self) + idx);
}

inline char		**ft_vstr_at(t_vstr *self, size_t idx)
{
	return (ft_vstr_begin(self) + idx);
}
