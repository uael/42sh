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

static char		g_var[MAX_INPUT + 1];
static char		g_val[MAX_INPUT + 1];

static inline void	assignset(t_map *map)
{
	uint32_t	it;
	char		*dvar;

	if (ft_mapget(map, g_var, &it))
	{
		free(((char **)map->vals)[it]);
		((char **)map->vals)[it] = ft_strdup(g_val);
	}
	else if (ft_mapput(map, dvar = ft_strdup(g_var), &it))
		((char **)map->vals)[it] = ft_strdup(g_val);
	else
		free(dvar);
}

inline int			sh_evalassign(t_tok *tok, t_deq *toks, t_map *map, char *ln)
{
	char		*eq;
	uint8_t		e;

	while (tok && tok->id == TOK_WORD)
	{
		if (!(eq = ft_strnchr(ln + tok->pos, '=', tok->len)) ||
			(eq == ln + tok->pos && ++tok->pos))
			break ;
		ft_strncpy(g_var, ln + tok->pos, eq - (ln + tok->pos));
		if (!sh_isname(g_var))
			break ;
		sh_wordresolve(g_val, eq, tok->len - (eq - ln), &e);
		if (!e)
			break ;
		assignset(map);
		g_sh->status = 0;
		tok = sh_toknext(toks);
	}
	return (YEP);
}
