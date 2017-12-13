/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval/bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:11:14 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bi/bi.h"

static inline t_bi_fn	bi_fn(char *exe)
{
	if (ft_strcmp("cd", exe) == 0)
		return (sh_bi_cd);
	if (ft_strcmp("echo", exe) == 0)
		return (sh_bi_echo);
	if (ft_strcmp("env", exe) == 0)
		return (sh_bi_env);
	if (ft_strcmp("exit", exe) == 0)
		return (sh_bi_exit);
	if (ft_strcmp("setenv", exe) == 0 || ft_strcmp("export", exe) == 0)
		return (sh_bi_setenv);
	if (ft_strcmp("unsetenv", exe) == 0 || ft_strcmp("unset", exe) == 0)
		return (sh_bi_unsetenv);
	return (NULL);
}

static inline void		eval_bi_av(t_sh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	if (av)
	{
		ft_vstr_ctor(av);
		ft_vstr_pushc(av, exe);
	}
	while ((end = sh_peek(self)) && end->id)
	{
		if (end->id == SH_TOK_WORD && av)
			ft_vstr_pushc(av, ft_tok_ident(end)->buf);
		else if (end->id != SH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		sh_next(self, NULL);
	}
	if (av)
	{
		ft_vstr_grow(av, 1);
		FT_INIT(ft_vstr_end(av), char *);
	}
}

inline int				sh_eval_bi(t_sh *self, t_job **pjob, t_tok *tok)
{
	t_vstr	av;
	t_bi_fn	bi;
	t_job	job;

	if (tok->id != SH_TOK_WORD)
		return (SH_NEXT);
	if (!(bi = bi_fn(ft_tok_ident(tok)->buf)))
		return (SH_NEXT);
	FT_INIT(&job, t_job);
	eval_bi_av(self, &av, ft_tok_ident(tok)->buf);
	self->st = bi(self, (int)av.len, av.buf, &job);
	job.av ? 0 : sh_bi_job(&job, av.buf, self->env.buf);
	if ((tok = sh_peek(self)) && sh_eval_heredoc(self, pjob, tok) == SH_OK)
	{
		sh_next(self, NULL);
		ft_job_pipe(*pjob);
		if (tok->val && tok->val->kind == TOKV_I32)
			job.pin = tok->val->val.i32;
	}
	ft_job_data(&job, self);
	*pjob = ft_worker_push(&self->worker, &job);
	return (SH_OK);
}
