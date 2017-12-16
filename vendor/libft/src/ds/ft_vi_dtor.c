/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_dtor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline void	ft_vi8_dtor(t_vi8 *self, t_dtor idtor)
{
	int8_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vi8_begin(self);
			while (item != ft_vi8_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vi8);
}

inline void	ft_vi16_dtor(t_vi16 *self, t_dtor idtor)
{
	int16_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vi16_begin(self);
			while (item != ft_vi16_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vi16);
}

inline void	ft_vi32_dtor(t_vi32 *self, t_dtor idtor)
{
	int32_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vi32_begin(self);
			while (item != ft_vi32_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vi16);
}

inline void	ft_vi64_dtor(t_vi64 *self, t_dtor idtor)
{
	int64_t	*item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vi64_begin(self);
			while (item != ft_vi64_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vi64);
}

inline void	ft_vstr_dtor(t_vstr *self, t_dtor idtor)
{
	char	**item;

	if (self->buf)
	{
		if (idtor)
		{
			item = ft_vstr_begin(self);
			while (item != ft_vstr_end(self))
				idtor(item++);
		}
		free(self->buf);
	}
	FT_INIT(self, t_vstr);
}
