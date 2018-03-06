/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 15:47:15 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/lib.h"
#include "libft/str.h"

inline char			*ft_join(char const *s1, char const *s2, char c)
{
	size_t	l1;
	size_t	l2;
	t_bool	ds;
	char	*r;

	l1 = ft_strlen(s1);
	if (!(l2 = ft_strlen(s2)) && !l1)
		return (NULL);
	ds = (t_bool)((!l1 || s1[l1 - 1] != c) && (!l2 || s2[0] != c));
	r = ft_malloc((l1 + l2 + ds + 1) * sizeof(char));
	if (l1)
		ft_strcpy(r, s1);
	if (ds)
		ft_strncpy(r + l1, &c, 1);
	if (l2)
		ft_strcpy(r + l1 + ds, s2);
	return (r);
}
