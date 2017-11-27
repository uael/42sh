/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_removen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline size_t	ft_dstr_removen(t_dstr *self, size_t idx, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if (idx >= (len = ft_dstr_size(self)))
		return (0);
	else if (idx == len - 1)
		return (ft_dstr_popn(self, n, out));
	else if (idx == 0)
		return (ft_dstr_shiftn(self, n, out));
	else
	{
		if (n > len)
			n = len;
		it = ft_dstr_at(self, idx);
		if (out)
			ft_memcpy(out, it, n * sizeof(char));
		ft_memmove(it, it + n, (len - idx - n + 1) * sizeof(char));
		self->len -= n;
		return (n);
	}
}
