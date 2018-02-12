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

static inline char	**makeenv(t_map *vars, t_bool *owned)
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

static inline int	makeargv(t_job *job, t_vec *av, t_deq *toks, char **ln)
{
	t_tok *tok;

	tok = sh_tokpeek(toks);
	while (tok)
		if (TOK_ISWORD(tok->id))
		{
			av ? sh_wordexplode(av, *ln + tok->pos, tok->len) : 0;
			tok = sh_toknext(toks);
		}
		else if (TOK_ISREDIR(tok->id))
		{
			if (sh_evalredir(job, toks, ln) == OUF)
			{
				av ? ft_vecdtor(av, (t_dtor)ft_pfree) : 0;
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
	t_tok		*tok;
	t_proc		*prc;
	t_bool		own;
	t_vec		av;
	t_redirs	r;

	ft_vecctor(&av, sizeof(char *));
	tok = sh_tokpeek(toks);
	while (!av.len)
	{
		if (!tok || !TOK_ISWORD(tok->id))
			return (NOP);
		sh_wordexplode(&av, *ln + tok->pos, tok->len);
		tok = sh_toknext(toks);
	}
	prc = ft_vecback((t_vec *)&job->procs);
	prc->argv = av.buf;
	ft_memcpy(&r, &prc->redirs, sizeof(t_redirs));
	ft_memset(&prc->redirs, 0, sizeof(t_redirs));
	if (!(own = (t_bool)ft_strcmp("true", prc->argv[0])) ||
		!ft_strcmp("false", prc->argv[0]))
	{
		ps_procbit(prc, (t_bool)(own ? 1 : 0));
		ft_memcpy(&prc->redirs, &r, sizeof(t_redirs));
		return (makeargv(job, NULL, toks, ln));
	}

	ps_procexe(prc, "PATH", prc->argv[0], makeenv(vars, &own));
	ft_memcpy(&prc->redirs, &r, sizeof(t_redirs));
	prc->ownenv = own;
	if (makeargv(job, &av, toks, ln) == OUF)
		return (OUF);
	*(char **)ft_vecpush(&av) = NULL;
	((t_proc *)ft_vecback((t_vec *)&job->procs))->argv = av.buf;
	return (YEP);
}
