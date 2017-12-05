/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/05 18:32:43 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include "msh.h"

inline t_st	sh_init_stream(t_sh *self, char **env, t_istream *stream)
{
	t_st st;

	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	ft_worker_ctor(&self->worker);
	if (ST_NOK(st = sh_initenv(&self->env, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_stream(&self->lexer, stream)))
		return (st);
	return (sh_lex(&self->lexer));
}

inline t_st	sh_init_file(t_sh *self, char **env, char const *filename)
{
	t_st st;

	FT_INIT(self, t_sh);
	ft_vstr_ctor(&self->env);
	ft_worker_ctor(&self->worker);
	if (ST_NOK(st = sh_initenv(&self->env, env)))
		return (st);
	if (ST_NOK(st = ft_lexer_init_file(&self->lexer, filename)))
		return (st);
	return (sh_lex(&self->lexer));
}

inline void	sh_dtor(t_sh *self)
{
	ft_vstr_dtor(&self->env, (void (*)(char **))ft_pfree);
	ft_lexer_dtor(&self->lexer);
	ft_worker_dtor(&self->worker);
}

inline t_st	sh_prompt(t_sh *self, char *prompt)
{
	size_t	l;
	char	cwd[PATH_MAX + 1];
	char	*p;
	char	**home;
	t_st	st;

	if (!(p = getcwd(cwd, PATH_MAX)))
		return (ENO);
	if (ISE(st = sh_envadd(&self->env, "PWD", p)))
		return (st);
	if ((home = sh_getenv(&self->env, "HOME")) && ft_strbegw(*home + 5, p))
	{
		if (p[l = ft_strlen(*home + 5)] != '\0')
			ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
		else
			p[1] = '\0';
		*p = '~';
	}
	ft_puts(0, p);
	ft_puts(0, prompt);
	return (OK);
}

inline t_st	msh(t_sh *self)
{
	t_tok		*tok;
	t_st		st;
	t_job		*prev;
	t_job		job;

	prev = NULL;
	ft_lexer_clean(&self->lexer);
	while (1)
	{
		if (!(tok = sh_next(self, NULL)))
			return (NOK);
		else if (tok->id == '\n')
		{
			if (ft_vec_size(&self->worker) &&
				ISE(st = ft_worker_run(&self->worker, self, &self->st)))
				ft_putf(2, "21sh: %e", ST_TOENO(st));
			return (OK);
		}
		else if (ft_strchr(";", tok->id))
		{
			if (ISE(st = ft_worker_run(&self->worker, self, &self->st)))
				ft_putf(2, "21sh: %e", ST_TOENO(st));
			ft_lexer_clean(&self->lexer);
			continue ;
		}
		else if (ft_strchr("\t ", tok->id))
			continue ;
		else if (tok->id == SH_TOK_PIPE)
		{
			if (!prev)
				return (ft_retf(NOK, "21sh: Unexpected token '%c'\n", tok->id));
			prev->op = JOB_OP_PIPE;
		}
		else if (ISE(st = sh_eval_job(self, &job, tok)))
			return (st);
		else if (ST_OK(st) && !(prev = ft_worker_push(&self->worker, &job)))
			return (st);
		else if (ST_OK(st))
		{
			if (prev->fn == (t_job_fn)sh_bi_exit)
			{
				if (ISE(st = ft_worker_run(&self->worker, self, &self->st)))
					ft_putf(2, "21sh: %e", ST_TOENO(st));
				exit(self->st);
			}
			continue ;
		}
		else
			return (ft_retf(NOK, "21sh: Unexpected token '%c'\n", tok->id));
	}
}
