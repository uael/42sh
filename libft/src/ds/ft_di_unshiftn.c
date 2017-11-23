/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_unshiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 09:38:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline int8_t	*ft_di8_unshiftn(t_di8 *self, size_t n)
{
	size_t	len;
	int8_t	*it;

	if (!n || !ft_di8_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
      self->cur -= n;
      return (ft_di8_begin(self));
    }
	else if (self->cur)
	{
      n -= self->cur;
      self->cur = 0;
    }
    it = ft_di8_begin(self);
    if ((len = ft_di8_size(self)))
      ft_memmove(it + n, it, (len + 1) * sizeof(int8_t));
    self->len += n;
	return it;
}

inline int16_t	*ft_di16_unshiftn(t_di16 *self, size_t n)
{
	size_t	len;
	int16_t	*it;

	if (!n || !ft_di16_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_di16_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_di16_begin(self);
	if ((len = ft_di16_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int16_t));
	self->len += n;
	return (it);
}

inline int32_t	*ft_di32_unshiftn(t_di32 *self, size_t n)
{
	size_t	len;
	int32_t	*it;

	if (!n || !ft_di32_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_di32_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_di32_begin(self);
	if ((len = ft_di32_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int32_t));
	self->len += n;
	return (it);
}

inline int64_t	*ft_di64_unshiftn(t_di64 *self, size_t n)
{
	size_t	len;
	int64_t	*it;

	if (!n || !ft_di64_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_di64_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_di64_begin(self);
	if ((len = ft_di64_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(int64_t));
	self->len += n;
	return (it);
}

inline char		**ft_dqstr_unshiftn(t_dqstr *self, size_t n)
{
	size_t	len;
	char	**it;

	if (!n || !ft_dqstr_grow(self, n))
		return (NULL);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_dqstr_begin(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_dqstr_begin(self);
	if ((len = ft_dqstr_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(char *));
	self->len += n;
	return (it);
}
