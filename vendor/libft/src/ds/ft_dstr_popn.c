/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_popn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline size_t	ft_dstr_popn(t_dstr *self, size_t n, char *out)
{
	size_t	len;
	char	*it;

	if ((len = ft_dstr_size(self)) == 0)
		return (0);
	else
	{
		if (n > len)
			n = len;
		self->len -= n;
		it = ft_dstr_end(self);
		if (out)
			ft_memcpy(out, it, n * sizeof(char));
		*it = '\0';
		return (n);
	}
}
