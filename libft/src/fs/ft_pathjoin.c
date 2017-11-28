/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 10:04:26 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/fs.h"
#include "libft/ds.h"

inline char		*ft_pathjoin(char const *p1, char const *p2)
{
	size_t	l1;
	size_t	l2;
	t_bool	ds;
	char	*r;

	l1 = ft_strlen(p1);
	if (!(l2 = ft_strlen(p2)) && !l1)
		return (NULL);
	ds = (t_bool)((!l1 || p1[l1 - 1] != '/') && (!l2 || p2[0] != '/'));
	if (!(r = malloc((l1 + l2 + ds + 1) * sizeof(char))))
		return (NULL);
	if (l1)
		ft_strcpy(r, p1);
	if (ds)
		ft_strcpy(r + l1, "/");
	if (l2)
		ft_strcpy(r + l1 + ds, p2);
	return (r);
}

static t_bool	ft_pathprev(t_dstr *pth, char *s, char *c)
{
	size_t i;

	if (*(s - 1) != '/')
	{
		ft_dstr_shiftn(pth, *(s + 2) == '/' ? 3 : 2, NULL);
		if ((s = ft_strrchr(c, '/')))
			ft_dstr_unshiftnc(pth, c, s - c + 1);
		else if (!ft_dstr_unshiftc(pth, '/') || !ft_dstr_prepend(pth, c))
			return (0);
	}
	else if (*(s + 2) != '/')
	{
		ft_dstr_popn(pth, *(s - 1) == '/' ? 3 : 2, NULL);
		if ((s = ft_strrchr(pth->buf, '/')))
			ft_dstr_popn(pth, ft_dstr_end(pth) - s - 1, NULL);
	}
	else
	{
		ft_dstr_removen(pth, s-- - pth->buf - (i = 1), 3, NULL);
		while (*--s != '/' && s >= pth->buf)
			++i;
		if (*s == '/')
			ft_dstr_removen(pth, s - pth->buf, i, NULL);
	}
	return (1);
}

inline char		*ft_pathreal(char const *p)
{
	t_dstr	pth;
	char	*s;
	char	c[4096 + 1];
	size_t	i;

	ft_dstr_ctor(&pth);
	if (!ft_dstr_append(&pth, p) || !getcwd(c, 4096) || !(i = ft_strlen(c)))
		return (NULL);
	if (c[i - 1] == '/')
		c[i - 1] = '\0';
	if (*pth.buf == '.' && *(pth.buf + 1) != '.')
	{
		s = pth.buf;
		ft_dstr_shiftn(&pth, *(s + 1) == '/' ? 2 : 1, NULL);
		if (!ft_dstr_unshiftc(&pth, '/') || !ft_dstr_prepend(&pth, c))
			return (NULL);
	}
	while ((s = ft_strstr(pth.buf, "..")))
		if (!ft_pathprev(&pth, s, c))
			return (NULL);
	return (pth.buf);
}

inline char		*ft_pathcat(char *dst, char const *src)
{
	size_t	l1;
	size_t	l2;
	t_bool	ds;

	l1 = ft_strlen(dst);
	if (!(l2 = ft_strlen(src)) && !l1)
		return (dst);
	ds = (t_bool)((!l1 || dst[l1 - 1] != '/') && (!l2 || src[0] != '/'));
	if (ds)
		ft_strcpy(dst + l1, "/");
	if (l2)
		ft_strcpy(dst + l1 + ds, src);
	return (dst);
}
