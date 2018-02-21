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

static void	onquote(int *quoted, char quote)
{
	if (quote == '\'')
	{
		if (*quoted == 0)
			*quoted = 1;
		else if (*quoted == 1)
			*quoted = 0;
	}
	else if (quote == '"')
	{
		if (*quoted == 0)
			*quoted = 2;
		else if (*quoted == 2)
			*quoted = 0;
	}
}

static int	globit(t_sds *word, t_vec *av, char *it)
{
	unsigned int	match;
	glob_t			globbuf;

	if (glob(it, GLOB_NOCHECK, NULL, &globbuf))
		return (THROW(WUT));
	if ((g_ifs && !*g_ifs) || !av)
	{
		ft_sdsapd(word, globbuf.gl_pathv[0]);
		match = 1;
		while (match < globbuf.gl_pathc)
		{
			*ft_sdspush(word) = ' ';
			ft_sdsapd(word, globbuf.gl_pathv[match++]);
		}
		globfree(&globbuf);
		return (YEP);
	}
	if (word->len)
		word->len = 0;
	match = 0;
	while (match < globbuf.gl_pathc)
		*(char **)ft_vecpush(av) = ft_strdup(globbuf.gl_pathv[match++]);
	globfree(&globbuf);
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
			onquote(&q, **words);
		else if (ft_strchr(g_ifs, **words))
			break ;
		else if (**words == '$')
		{
			if (q != 1 && (st = sh_expdollars(word, words, &glist, q == 2)))
				return (globdone(&glist, st));
		}
		else if (**words == '\\')
		{
			if ((st = sh_expbackslash(word, words, (t_bool)(q != 0))))
				return (globdone(&glist, st));
		}
		else
			*ft_sdspush(word) = **words;
	return (globthem(word, words, av, &glist));
}
