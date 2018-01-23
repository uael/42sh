/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/eval.h"

static int		evalexport(t_map *vars)
{
	uint32_t it;

	if (!vars->len)
		return (NOP);
	it = 0;
	while (it < vars->cap)
	{
		if (BUCKET_ISPOPULATED(vars->bucks, it))
			sh_varset(((char **)vars->keys)[it], ((char **)vars->vals)[it]);
		++it;
	}
	ft_mapdtor(vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
	return (YEP);
}

inline int		sh_evalsimple(t_job *job, int fd, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_map	vars;
	int		st;

	(void)fd;
	ft_mapctor(&vars, g_strhash, sizeof(char *), sizeof(char *));
	if ((tok = sh_tokpeek(toks))->id == TOK_WORD)
	{
		if (ft_strchr(tok->val, '='))
			sh_evalassign(toks, &vars);
		if ((st = sh_evalargv(job, &vars, toks, ln)) == ERR)
			return (st);
		else if (st)
			return (evalexport(&vars));
	}
	return (YEP);
}
