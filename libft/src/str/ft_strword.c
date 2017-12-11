/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:40:58 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 19:29:17 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/str.h"

inline size_t	ft_strword(char const *s, char c, char e)
{
	size_t n;

	n = 0;
	while (*s && *s != e)
		if (*s == c)
			++s;
		else if (++n && *++s)
			while (*s && *s != c && *s != e)
				++s;
	return (n);
}
