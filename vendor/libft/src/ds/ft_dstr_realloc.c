/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline t_bool	ft_dstr_realloc(t_dstr *self, size_t n)
{
	void *buf;

	if (self->cap == n)
		return (1);
	if (!(buf = ft_realloc(self->buf, self->len, n * sizeof(char))))
		return (0);
	self->buf = buf;
	if (self->len > (self->cap = n))
		self->len = n;
	return (1);
}
