/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nusht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds.h"

inline void		*ft_deqnusht(t_deq *self, size_t n)
{
	size_t	len;
	void	*it;

	ft_deqgrow(self, n);
	if (self->cur >= n)
	{
		self->cur -= n;
		return (ft_deqbeg(self));
	}
	else if (self->cur)
	{
		n -= self->cur;
		self->cur = 0;
	}
	it = ft_deqbeg(self);
	if ((len = ft_deqlen(self)))
		ft_memmove((char *)it + (n * self->isz), it,
			(len + 1) * self->isz);
	self->len += n;
	return (it);
}

inline char		*ft_sdsnusht(t_sds *self, size_t n)
{
	size_t	len;
	char	*it;

	ft_sdsgrow(self, n);
	it = ft_sdsbeg(self);
	if ((len = ft_sdslen(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(char));
	else
		it[n] = '\0';
	self->len += n;
	return (it);
}

inline void		*ft_vecnusht(t_vec *self, size_t n)
{
	size_t	len;
	void	*it;

	ft_vecgrow(self, n);
	it = ft_vecbeg(self);
	if ((len = ft_veclen(self)))
		ft_memmove((char *)it + (n * self->isz), it,
			(len + 1) * self->isz);
	self->len += n;
	return (it);
}
