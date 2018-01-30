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

#include <stdarg.h>

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

static inline int	vinitf(char const *f, va_list ap)
{
	char	*sp;

	while ((sp = ft_strchr(f, '%')))
		if (*((f = ++sp + 1) - 1) == 'd')
			ft_memset(va_arg(ap, void *), 0, va_arg(ap, size_t));
		else if (*sp == 'c')
			ft_memset(va_arg(ap, void *), 0, sizeof(char));
		else if (*sp == 's')
			ft_memset(va_arg(ap, void *), 0, sizeof(short));
		else if (*sp == 'i')
			ft_memset(va_arg(ap, void *), 0, sizeof(int));
		else if (*sp == 'l' && *(sp + 1) == 'l')
			ft_memset(va_arg(ap, void *), 0, sizeof(long long int));
		else if (*sp == 'l')
			ft_memset(va_arg(ap, void *), 0, sizeof(long));
		else if (ft_isdigit(*sp))
		{
			ft_memset(va_arg(ap, void *), 0, (size_t)ft_atoi(sp));
			while (ft_isdigit(*sp))
				++sp;
		}
	return (0);
}

int					ft_initf(char const *fmt, ...)
{
	va_list	ap;
	int		r;

	va_start(ap, fmt);
	r = vinitf(fmt, ap);
	va_end(ap);
	return (r);
}
