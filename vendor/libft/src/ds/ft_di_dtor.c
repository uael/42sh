/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_dtor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:26:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline void	ft_di8_dtor(t_di8 *self, t_dtor idtor)
{
	int8_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_di8_begin(self);
			while (item != ft_di8_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_di8);
}

inline void	ft_di16_dtor(t_di16 *self, t_dtor idtor)
{
	int16_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_di16_begin(self);
			while (item != ft_di16_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_di16);
}

inline void	ft_di32_dtor(t_di32 *self, t_dtor idtor)
{
	int32_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_di32_begin(self);
			while (item != ft_di32_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_di16);
}

inline void	ft_di64_dtor(t_di64 *self, t_dtor idtor)
{
	int64_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_di64_begin(self);
			while (item != ft_di64_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_di64);
}

inline void	ft_dqstr_dtor(t_dqstr *self, t_dtor idtor)
{
	char	**item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_dqstr_begin(self);
			while (item != ft_dqstr_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_dqstr);
}
