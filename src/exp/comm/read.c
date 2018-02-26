/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/comm/read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

static void	onifs(char const *out, int *copying, t_sds *word, t_vec *av)
{
	if (!ft_strchr(g_ifsw, *out))
	{
		if (*copying == 2)
		{
			*copying = 0;
			return ;
		}
		*copying = 0;
	}
	else
	{
		if (*out == '\n' && *(out + 1))
		{
			*copying == 1 ? (*copying = 3) : 0;
			return ;
		}
		else
		{
			if (*copying != 1 && *copying != 3)
				return ;
			*copying = 2;
		}
	}
	*(char **)ft_vecpush(av) = ft_strdup(word->len ? word->buf : "");
	word->len = 0;
}

static int	commsplit(char *buf, t_sds *w, t_vec *av)
{
	char	*out;
	int		copying;
	int		eol;

	out = buf - 1;
	copying = 0;
	eol = 0;
	while (*++out)
		if (ft_strchr(g_ifs, *out))
			onifs(out, &copying, w, av);
		else
		{
			if (copying == 3)
			{
				*(char **)ft_vecpush(av) = ft_strdup(w->len ? w->buf : "");
				w->len = 0;
			}
			copying = 1;
			if (*out == '\n')
				++eol;
			else
				eol = 0;
			*ft_sdspush(w) = *out;
		}
	return (eol);
}

void		sh_expcommread(int fd, t_sds *word, t_vec *av)
{
	ssize_t	ret;
	char	buf[128 + 1];
	int		eol;

	eol = 0;
	while ((ret = read(fd, buf, 128)) > 0)
		if (!av)
		{
			eol += ret;
			ft_sdsmpush(word, buf, (size_t)ret);
		}
		else
		{
			buf[ret] = '\0';
			eol = commsplit(buf, word, av);
		}
	while (eol-- && word->len > 0 && *ft_sdsback(word) == '\n')
		word->buf[--word->len] = '\0';
}
