/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_ctor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline void	ft_di8_ctor(t_di8 *self)
{
	FT_INIT(self, t_di8);
}

inline void	ft_di16_ctor(t_di16 *self)
{
	FT_INIT(self, t_di16);
}

inline void	ft_di32_ctor(t_di32 *self)
{
	FT_INIT(self, t_di16);
}

inline void	ft_di64_ctor(t_di64 *self)
{
	FT_INIT(self, t_di64);
}

inline void	ft_dqstr_ctor(t_dqstr *self)
{
	FT_INIT(self, t_dqstr);
}
