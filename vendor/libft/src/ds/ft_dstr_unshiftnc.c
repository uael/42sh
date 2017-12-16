/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_unshiftnc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/dstr.h"

inline char	*ft_dstr_unshiftnc(t_dstr *self, char const *items, size_t n)
{
	char *it;

	if (!(it = ft_dstr_unshiftn(self, n)))
		return (NULL);
	ft_memcpy(it, items, n * sizeof(char));
	return (it);
}
