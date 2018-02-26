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
#include "ush/exp.h"

static char		g_var[MAX_INPUT + 1];

static inline void	assignset(t_map *map, char *val)
{
	uint32_t	it;
	char		*dvar;

	if (ft_mapget(map, g_var, &it))
	{
		free(((char **)map->vals)[it]);
		((char **)map->vals)[it] = val;
	}
	else if (ft_mapput(map, dvar = ft_strdup(g_var), &it))
		((char **)map->vals)[it] = val;
	else
	{
		free(dvar);
		free(val);
	}
}

inline int			sh_evalassign(t_tok *tok, t_deq *toks, t_map *map, char *ln)
{
	char		*eq;
	t_sds		val;

	while (tok && tok->id == TOK_WORD)
	{
		if (!(eq = ft_strnchr(ln + tok->pos, '=', tok->len)) ||
			(eq == ln + tok->pos && ++tok->pos))
			break ;
		ft_strncpy(g_var, ln + tok->pos, eq - (ln + tok->pos));
		if (!sh_isname(g_var))
			break ;
		ft_sdsctor(&val);
		sh_expword(&val, eq + 1, tok->len - (eq - ln - tok->pos) - 1);
		assignset(map, val.len ? val.buf : ft_strdup(""));
		g_sh->status = 0;
		tok = sh_toknext(toks);
	}
	return (YEP);
}
