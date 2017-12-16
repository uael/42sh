/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_putn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline char	*ft_dstr_putn(t_dstr *self, size_t idx, size_t n)
{
	size_t	len;
	char	*it;

	if (idx == 0)
		return (ft_dstr_unshiftn(self, n));
	else if (idx == (len = ft_dstr_size(self)))
		return (ft_dstr_pushn(self, n));
	else if (n == 0 || idx > len)
		return (NULL);
	else
	{
		ft_dstr_grow(self, n);
		it = ft_dstr_begin(self) + idx;
		ft_memmove(it + n, it, (len - idx + 1) * sizeof(char));
		self->len += n;
		return (it);
	}
}
