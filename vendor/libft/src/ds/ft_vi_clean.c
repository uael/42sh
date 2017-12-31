/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vi_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 14:18:33 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/vec.h"

inline size_t	ft_vi8_clean(t_vi8 *self, size_t n, t_dtor idtor)
{
	int8_t	*item;
	int8_t	*it;
	int8_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vi8_begin(self);
	end = ft_vi8_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int8_t));
	return (n);
}

inline size_t	ft_vi16_clean(t_vi16 *self, size_t n, t_dtor idtor)
{
	int16_t	*item;
	int16_t	*it;
	int16_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vi16_begin(self);
	end = ft_vi16_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int16_t));
	return (n);
}

inline size_t	ft_vi32_clean(t_vi32 *self, size_t n, t_dtor idtor)
{
	int32_t	*item;
	int32_t	*it;
	int32_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vi32_begin(self);
	end = ft_vi32_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int32_t));
	return (n);
}

inline size_t	ft_vi64_clean(t_vi64 *self, size_t n, t_dtor idtor)
{
	int64_t	*item;
	int64_t	*it;
	int64_t	*end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vi64_begin(self);
	end = ft_vi64_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(int64_t));
	return (n);
}

inline size_t	ft_vstr_clean(t_vstr *self, size_t n, t_dtor idtor)
{
	char	**item;
	char	**it;
	char	**end;

	if (!n || self->len == 0)
		return (0);
	if (n > self->len)
		n = self->len;
	it = ft_vstr_begin(self);
	end = ft_vstr_at(self, n);
	if (idtor)
	{
		item = it - 1;
		while (++item != end)
			idtor(item);
	}
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(char *));
	return (n);
}
