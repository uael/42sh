/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static void		assignset(t_map *map, char *var, char *val)
{
	uint32_t	it;
	char		*dvar;
	t_sds		v;

	ft_sdsctor(&v);
	ft_sdsapd(&v, val);
	if (ft_mapget(map, var, &it))
		((char **)map->vals)[it] = v.buf;
	else if (ft_mapput(map, dvar = ft_strdup(var), &it))
		((char **)map->vals)[it] = v.buf;
	else
	{
		free(dvar);
		ft_sdsdtor(&v);
	}
}

inline int		sh_evalassign(t_deq *toks, t_map *map, char *ln)
{
	char		*assign;
	int			st;
	t_tok		*tok;
	char		buf[MAX_INPUT];

	st = NOP;
	tok = sh_tokpeek(toks);
	ft_strncpy(buf, ln + tok->pos, tok->len);
	while ((assign = ft_strchr(buf, '=')))
		if (assign == buf)
		{
			tok->len = 0;
			break ;
		}
		else if (sh_isname(buf))
		{
			st = YEP;
			*assign = '\0';
			assignset(map, buf, assign + 1);
			g_sh->status = 0;
			if (!(tok = sh_toknext(toks)) || tok->id != TOK_WORD)
				break ;
		}
		else
			break ;
	return (st);
}
