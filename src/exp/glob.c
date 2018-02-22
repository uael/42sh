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

#include <glob.h>

#include "ush/exp.h"

static int	globdone(t_vec *glist, int st)
{
	ft_vecdtor(glist, (t_dtor)ft_pfree);
	return (st);
}

/*
** TODO: use the mc glob
*/

static int	globit(t_sds *word, t_vec *av, char *it)
{
	uint32_t	match;
	glob_t		gbuf;
	const int	flags = GLOB_NOCHECK | (ft_strchr(it, ',') ? GLOB_BRACE : 0);

	if (glob(it, flags, NULL, &gbuf))
		return (THROW(WUT));
	if ((g_ifs && !*g_ifs) || !av)
	{
		ft_sdsapd(word, gbuf.gl_pathv[0]);
		match = 1;
		while (match < gbuf.gl_pathc)
		{
			*ft_sdspush(word) = ' ';
			ft_sdsapd(word, gbuf.gl_pathv[match++]);
		}
		globfree(&gbuf);
		return (YEP);
	}
	word->len ? (word->len = 0) : 0;
	match = 0;
	while (match < gbuf.gl_pathc)
		*(char **)ft_vecpush(av) = ft_strdup(gbuf.gl_pathv[match++]);
	globfree(&gbuf);
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
