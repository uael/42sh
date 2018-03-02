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
#include "ush/func.h"

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

static inline int	makeargv(t_proc *proc, t_vec *av, t_deq *toks, char **ln)
{
	int		st;
	t_tok	*tok;

	tok = sh_tokpeek(toks);
	while (tok)
		if (sh_tokis(tok, TOKS_WORD))
		{
			av && tok->id != TOK_DRBRA ?
				sh_expwords(av, *ln + tok->pos, tok->len) : 0;
			tok = sh_toknext(toks);
		}
		else if (sh_tokis(tok, TOKS_REDIR))
		{
			if ((st = sh_evalredir(proc, toks, ln)))
				return (st);
			tok = sh_tokpeek(toks);
		}
		else
			break ;
	return (YEP);
}

static inline char	*explodesome(t_vec *av, t_deq *t, char **ln)
{
	t_tok		*tok;

	ft_vecctor(av, sizeof(char *));
	tok = sh_tokpeek(t);
	if (tok->id == TOK_DLBRA)
	{
		*(char **)ft_vecpush(av) = ft_strdup("test");
		sh_toknext(t);
	}
	else
		while (!av->len)
		{
			if (!tok || !sh_tokis(tok, TOKS_WORD))
				return (NULL);
			sh_expwords(av, *ln + tok->pos, tok->len);
			tok = sh_toknext(t);
		}
	return (((char **)av->buf)[0]);
}

static inline void	fncheck(t_proc *prc, char const *bin)
{
	if (sh_funcget(bin))
	{
		prc->kind = PROC_FN;
		prc->u.fn.cb = (t_proccb *)sh_evalfn;
		prc->u.fn.dtor = NULL;
		prc->u.fn.data = NULL;
	}
}

inline int			sh_evalargv(t_proc *prc, t_map *v, t_deq *toks, char **ln)
{
	t_bool	own;
	t_vec	av;
	int		st;
	char	*bin;

	if (!(bin = explodesome(&av, toks, ln)))
		return (NOP);
	if (!(own = (t_bool)ft_strcmp("true", bin)) || !ft_strcmp("false", bin))
	{
		ft_vecdtor(&av, (t_dtor)ft_pfree);
		ps_procbit(prc, (t_bool)(own ? 1 : 0));
		return (makeargv(prc, NULL, toks, ln));
	}
	ps_procexe(prc, "PATH", bin, makeenv(v, &own));
	fncheck(prc, bin);
	prc->ownenv = own;
	if ((st = makeargv(prc, &av, toks, ln)))
	{
		ft_vecdtor(&av, (t_dtor)ft_pfree);
		return (st);
	}
	*(char **)ft_vecpush(&av) = NULL;
	prc->argv = av.buf;
	return (YEP);
}
