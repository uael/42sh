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

#include <glob.h>
#include "ush/eval.h"

static inline char		**makeenv(t_map *vars, t_bool *owned)
{
	t_vec		*e;
	char		**envv;
	uint32_t	it;

	if (!(*owned = (t_bool)(vars->occupieds > 0)))
		return (environ);
	ft_vecctor(e = alloca(sizeof(t_vec)), sizeof(char *));
	envv = environ;
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

static inline int		makeargv(t_job *job, glob_t *av, t_deq *toks, char **ln)
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
				av ? globfree(av) : 0;
				return (OUF);
			}
			tok = sh_tokpeek(toks);
		}
		else
			break ;
	return (YEP);
}

static inline t_proc	*explodesome(t_job *job, t_deq *t, char **ln)
{
	t_tok		*tok;
	t_proc		*prc;

	tok = sh_tokpeek(t);
	prc = ft_vecback((t_vec *)&job->procs);
	while (!prc->argv.gl_pathc)
	{
		if (!tok || !TOK_ISWORD(tok->id))
			return (NULL);
		sh_wordexplode(&prc->argv, *ln + tok->pos, tok->len);
		tok = sh_toknext(t);
	}
	return (prc);
}

inline int				sh_evalargv(t_job *j, t_map *v, t_deq *toks, char **ln)
{
	t_proc		*prc;
	t_bool		own;
	t_redirs	r;
	glob_t		g;

	if (!(prc = explodesome(j, toks, ln)))
		return (NOP);
	ft_memcpy(&r, &prc->redirs, sizeof(t_redirs));
	ft_memcpy(&g, &prc->argv, sizeof(glob_t));
	ft_memset(&prc->redirs, 0, sizeof(t_redirs));
	if (!(own = (t_bool)ft_strcmp("true", prc->argv.gl_pathv[0])) ||
		!ft_strcmp("false", prc->argv.gl_pathv[0]))
	{
		ps_procbit(prc, (t_bool)(own ? 1 : 0));
		ft_memcpy(&prc->redirs, &r, sizeof(t_redirs));
		return (makeargv(j, NULL, toks, ln));
	}
	ps_procexe(prc, "PATH", prc->argv.gl_pathv[0], makeenv(v, &own));
	ft_memcpy(&prc->redirs, &r, sizeof(t_redirs));
	ft_memcpy(&prc->argv, &g, sizeof(glob_t));
	prc->ownenv = own;
	if (makeargv(j, &prc->argv, toks, ln) == OUF)
		return (OUF);
	return (YEP);
}
