/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_unshiftn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline char	*ft_dstr_unshiftn(t_dstr *self, size_t n)
{
	size_t	len;
	char	*it;

	if (!n || !ft_dstr_grow(self, n))
		return (NULL);
	it = ft_dstr_begin(self);
	if ((len = ft_dstr_size(self)))
		ft_memmove(it + n, it, (len + 1) * sizeof(char));
	else
		it[n] = '\0';
	self->len += n;
	return (it);
}
