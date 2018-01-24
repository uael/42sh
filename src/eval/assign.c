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

	if (ft_mapget(map, var, &it))
		((char **)map->vals)[it] = ft_strdup(val);
	else if (ft_mapput(map, dvar = ft_strdup(var), &it))
		((char **)map->vals)[it] = ft_strdup(val);
	else
		free(dvar);
}

inline int		sh_evalassign(t_deq *toks, t_map *map)
{
	t_tok		*tok;
	char		*assign;
	int			st;

	st = NOP;
	tok = sh_tokpeek(toks);
	while ((assign = ft_strchr(tok->val, '=')))
		if (assign == tok->val)
		{
			ft_sdssht((t_sds *)tok, NULL);
			break ;
		}
		else if (sh_isname(tok->val))
		{
			st = YEP;
			*assign = '\0';
			assignset(map, tok->val, assign + 1);
			g_shstatus = 0;
			if (!(tok = sh_toknext(toks)) || tok->id != TOK_WORD)
				break ;
		}
		else
			break ;
	return (st);
}
