/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_shiftn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline size_t	ft_dstr_shiftn(t_dstr *self, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if (!n || (len = ft_dstr_size(self)) == 0)
		return (0);
	if (n > len)
		n = len;
	it = ft_dstr_begin(self);
	if (out)
		ft_memcpy(out, it, n * sizeof(char));
	if (self->len -= n)
		ft_memmove(it, it + n, (self->len + 1) * sizeof(char));
	return (n);
}
