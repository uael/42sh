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

static char		**buildenv(t_map *vars, t_bool *owned)
{
	t_vec		*e;
	char		**envv;
	uint32_t	it;

	if (!(*owned = (t_bool)(vars->occupieds > 0)))
		return (g_env);
	ft_vecctor(e = alloca(sizeof(t_vec)), sizeof(char *));
	envv = g_env;
	while (*envv)
		*(char **)ft_vecpush(e) = ft_strdup(*envv++);
	it = 0;
	while (it < vars->cap)
	{
		if (BUCKET_ISPOPULATED(vars->bucks, it))
			ft_setenv(e, ((char **)vars->keys)[it], ((char **)vars->vals)[it]);
		++it;
	}
	ft_mapdtor(vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
	*(char **)ft_vecpush(e) = NULL;
	return (e->buf);
}

inline int		sh_evalargv(t_job *job, t_map *vars, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_vec	av;
	int		st;
	t_proc	*prc;

	if (!(tok = sh_tokpeek(toks)) || tok->id != TOK_WORD)
		return (NOP);
	prc = ft_vecpush((t_vec *)&job->processes);
	ft_vecctor(&av, sizeof(char *));
	if (*tok->val == '$' && tok->len > 1)
		sh_wordexpand((t_sds *)tok);
	if ((st = sh_procctor(prc, "PATH", tok->val, buildenv(vars, &prc->ownenv))))
	{
		sh_proccnf(prc, *ln, tok, st);
		tok = sh_toknext(toks);
		while (tok && tok->id == TOK_WORD)
			tok = sh_toknext(toks);
	}
	else
	{
		*(char **)ft_vecpush(&av) = ft_strdup(tok->val);
		tok = sh_toknext(toks);
		while (tok && tok->id == TOK_WORD)
		{
			if (*tok->val == '$' && tok->len > 1)
				sh_wordexpand((t_sds *)tok);
			*(char **)ft_vecpush(&av) = ft_strdup(tok->val);
			tok = sh_toknext(toks);
		}
	}
	*(char **)ft_vecpush(&av) = NULL;
	prc->argv = av.buf;
	return (YEP);
}
