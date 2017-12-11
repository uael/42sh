/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:53:23 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 17:41:44 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline char	**ft_strsplit(char const *s, char c)
{
	size_t		nw;
	char const	*chr;
	char		**r;
	char		**ptr;

	nw = ft_strword(s, c, '\0');
	if (!(r = malloc((nw + 1) * sizeof(char *))))
		return (NULL);
	ptr = r;
	while (*s)
		if (*s == c)
			++s;
		else
		{
			chr = s;
			while (*chr && *chr != c)
				++chr;
			nw = chr - s;
			if (!(*ptr = malloc((nw + 1) * sizeof(char))))
				return (NULL);
			ft_strncpy(*ptr++, s, nw)[nw] = '\0';
			s += nw;
		}
	*ptr = NULL;
	return (r);
}
