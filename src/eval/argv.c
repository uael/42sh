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

static char			**mev(t_map *vars, t_bool *owned)
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

static int			procbool(t_job *job, t_tok *tok, t_deq *toks, char **ln)
{
	tok = sh_toknext(toks);
	while (tok)
		if (tok->id == TOK_WORD)
			tok = sh_toknext(toks);
		else if (TOK_ISREDIR(tok->id))
		{
			if (sh_evalredir(job, toks, ln) == OUF)
				return (OUF);
			tok = sh_tokpeek(toks);
		}
		else
			break ;
	return (YEP);
}

static inline void	expand(t_tok *tok, t_deq *toks)
{
	if (*tok->val == '$' && tok->len > 1 && sh_isname(tok->val))
	{
		sh_wordexpand((t_sds *)tok);
		sh_tokexplode(tok, toks);
	}
}

static inline int	argv(t_job *job, t_vec *av, t_deq *toks, char **ln)
{
	t_tok *tok;

	*(char **)ft_vecpush(av) = ft_strdup(sh_tokpeek(toks)->val);
	tok = sh_toknext(toks);
	while (tok)
		if (tok->id == TOK_WORD)
		{
			expand(tok, toks);
			*(char **)ft_vecpush(av) = ft_strdup(tok->val);
			tok = sh_toknext(toks);
		}
		else if (TOK_ISREDIR(tok->id))
		{
			if (sh_evalredir(job, toks, ln) == OUF)
			{
				free(((t_proc *)ft_vecback((t_vec *)&job->procs))->u.exe);
				ft_vecdtor(av, (t_dtor)ft_pfree);
				ft_vecpop((t_vec *)&job->procs, NULL);
				return (OUF);
			}
			tok = sh_tokpeek(toks);
		}
		else
			break ;
	return (YEP);
}

inline int			sh_evalargv(t_job *job, t_map *vars, t_deq *toks, char **ln)
{
	t_tok	*tok;
	t_vec	av;
	int		st;
	t_proc	*prc;

	if (!(tok = sh_tokpeek(toks)) || (tok->id != TOK_WORD &&
		!TOK_ISBOOL(tok->id)))
		return (NOP);
	prc = ft_vecpush((t_vec *)&job->procs);
	ft_vecctor(&av, sizeof(char *));
	expand(tok, toks);
	if (tok->id == TOK_TRUE || tok->id == TOK_FALSE)
	{
		sh_procbool(prc, (t_bool)(tok->id == TOK_FALSE));
		if (procbool(job, tok, toks, ln) == OUF)
		{
			ft_vecpop((t_vec *)&job->procs, NULL);
			return (OUF);
		}
	}
	else if ((st = sh_procctor(prc, "PATH", tok->val, mev(vars, &prc->ownenv))))
	{
		sh_proccnf(prc, *ln, tok, st);
		tok = sh_toknext(toks);
		while (tok && (tok->id == TOK_WORD || TOK_ISREDIR(tok->id)))
			tok = sh_toknext(toks);
	}
	else
	{
		if (argv(job, &av, toks, ln) == OUF)
			return (OUF);
		*(char **)ft_vecpush(&av) = NULL;
		((t_proc *)ft_vecback((t_vec *)&job->procs))->argv = av.buf;
	}
	return (YEP);
}
