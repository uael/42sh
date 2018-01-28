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

#define ISCMDM(T) ((T)->id==TOK_WORD||TOK_ISBOOL((T)->id)||TOK_ISREDIR((T)->id))
#define MSG1(E, B) ft_strcat(ft_strcpy(B, E), ": permission denied")
#define MSG2(E, B) ft_strcat(ft_strcpy(B, E), ": Command not found")
#define MSG(ST, E, B) ft_strdup((ST)==PROC_NORIGHTS?MSG1(E,B):MSG2(E,B))

static char			g_buf[PATH_MAX];

static char			**makeenv(t_map *vars, t_bool *owned)
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

	av ? *(char **)ft_vecpush(av) = ft_strdup(sh_tokpeek(toks)->val) : 0;
	tok = sh_toknext(toks);
	while (tok)
		if (tok->id == TOK_WORD || TOK_ISBOOL(tok->id))
		{
			av ? sh_tokexpand(tok, toks) : 0;
			av ? *(char **)ft_vecpush(av) = ft_strdup(tok->val) : 0;
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
	t_tok	*tok;
	int		st;
	t_proc	*prc;
	t_bool	own;
	t_vec	av;

	sh_tokexpand(tok = sh_tokpeek(toks), toks);
	prc = ft_vecback((t_vec *)&job->procs);
	if (TOK_ISBOOL(tok->id))
	{
		sh_procbit(prc, (t_bool)(tok->id == TOK_FALSE));
		return (makeargv(job, NULL, toks, ln));
	}
	else if ((st = sh_procexe(prc, "PATH", tok->val, makeenv(vars, &own))))
	{
		sh_procerr(prc, MSG(st, tok->val, g_buf), *ln, tok->pos)->st = st;
		prc->ownenv = own;
		return (makeargv(job, NULL, toks, ln));
	}
	ft_vecctor(&av, sizeof(char *));
	if (makeargv(job, &av, toks, ln) == OUF)
		return (OUF);
	*(char **)ft_vecpush(&av) = NULL;
	((t_proc *)ft_vecback((t_vec *)&job->procs))->argv = av.buf;
	return (YEP);
}
