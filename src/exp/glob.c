/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/comm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

static int	globdone(t_vec *glist, int st)
{
	ft_vecdtor(glist, (t_dtor)ft_pfree);
	return (st);
}

static int	globexpall(t_glob *gbuf, t_sds *word, t_vec *av)
{
	uint32_t	match;
	char		*str;

	match = 0;
	while (match < gbuf->gl_pathc)
	{
		str = gbuf->gl_pathv[match++];
		if ((g_ifs && !*g_ifs) || !av)
		{
			sh_exp(&str, word, NULL);
			if (match < gbuf->gl_pathc)
				*ft_sdspush(word) = ' ';
		}
		else
		{
			sh_exp(&str, word, av);
			if (word->len)
			{
				*(char **)ft_vecpush(av) = ft_strdup(word->buf);
				word->len = 0;
			}
		}
	}
	ft_globfree(gbuf);
	return (YEP);
}

static int	globit(t_sds *word, t_vec *av, char *it)
{
	uint32_t	match;
	t_glob		gbuf;

	ft_bzero(&gbuf, sizeof(t_glob));
	if (ft_glob(it, GLOBUX_NOCHECK | GLOBUX_BRACE, &gbuf))
		return (ft_throw(WUT, FT_DBG));
	if ((gbuf.gl_flags & GLOBUX_NOMATCH) && gbuf.gl_pathc > 1)
		return (globexpall(&gbuf, word, av));
	match = 0;
	if ((g_ifs && !*g_ifs) || !av)
	{
		ft_sdsapd(word, gbuf.gl_pathv[0]);
		while (++match < gbuf.gl_pathc)
		{
			*ft_sdspush(word) = ' ';
			ft_sdsapd(word, gbuf.gl_pathv[match]);
		}
	}
	else
		while (match < gbuf.gl_pathc)
			*(char **)ft_vecpush(av) = ft_strdup(gbuf.gl_pathv[match++]);
	ft_globfree(&gbuf);
	return (YEP);
}

static int	globthem(t_sds *word, char **words, t_vec *av, t_vec *glist)
{
	size_t	i;
	int		st;

	--*words;
	*(char **)ft_vecpush(glist) = ft_strdup(word->len ? word->buf : "");
	word->len = 0;
	i = 0;
	st = 0;
	while (!st && i < glist->len)
		st = globit(word, av, *(char **)ft_vecat(glist, i++));
	return (globdone(glist, st));
}

int			sh_expglob(t_sds *word, char **words, t_vec *av)
{
	t_vec	glist;
	int		q;
	int		st;

	q = 0;
	ft_vecctor(&glist, sizeof(char *));
	--*words;
	while (*++*words)
		if (**words == '\'' || **words == '"')
			sh_exponquote(&q, **words);
		else if (ft_strchr(g_ifs, **words))
			break ;
		else if (**words == '$')
		{
			if (q != 1 && (st = sh_expdollars(word, words, &glist, q == 2)))
				return (globdone(&glist, st));
		}
		else
			*ft_sdspush(word) = **words;
	return (globthem(word, words, av, &glist));
}
