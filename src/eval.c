/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/07 15:11:57 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

inline t_st	sh_eval_bi(t_sh *self, t_job *job, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_dstr		*ident;
	t_bi_fn		bi;

	if (!tok || tok->id != SH_TOK_WORD)
		return (NOK);
	ident = ft_tok_ident(tok);
	if (!(bi = sh_bi(ident->buf)))
		return (NOK);
	FT_INIT(job, t_job);
	if (ISE(st = sh_exe_av(self, &av, ident->buf)))
		return (st);
	self->st = bi(self, (int)av.len, av.buf, job);
	if (!job->av)
		sh_bi_job(job, av.buf, self->env.buf);
	return (OK);
}

inline t_st	sh_eval_job(t_sh *self, t_job *job, t_tok *tok)
{
	t_vstr		av;
	t_st		st;
	t_dstr		*ident;

	if (!tok || tok->id != SH_TOK_WORD)
		return (NOK);
	ident = ft_tok_ident(tok);
	if (ISE(st = sh_exe_av(self, &av, ident->buf)))
		return (st);
	if (ISE(st = ft_job_exe(job, "PATH", av.buf, self->env.buf)))
		return (ft_retf(NOK, N_SH"%s: %e\n", av.buf[0], ST_TOENO(st)));
	else if (ST_NOK(st))
		return (ft_retf(NOK, N_SH"%s: Command not found\n", av.buf[0]));
	return (OK);
}

inline t_st	sh_reduce(t_sh *self)
{
	t_sz	sz;
	t_tok	*tok;
	t_tok	*next;
	t_dstr	*s;
	char	*beg;
	char	c;
	size_t	l;
	t_src	*src;

	if (SZ_NOK(sz = ft_lexer_until(&self->lexer, '\n')))
		return (SZ_TOST(sz));
	tok = (t_tok *)ft_deq_begin(&self->lexer.toks) - 1;
	while (++tok != ft_deq_end(&self->lexer.toks))
	{
		if (tok->id == SH_TOK_HEREDOC && !tok->val)
		{
			if ((next = tok + 1) == ft_deq_end(&self->lexer.toks) ||
				next->id != SH_TOK_WORD)
				return (ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id));
			if (ft_deq_size(&self->lexer.srcs) == 0 ||
				!(src = ft_deq_at(&self->lexer.srcs, 0)))
				return (ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id));
			s = ft_tokv_ident(next->val);
			beg = ft_strdup(s->buf);
			l = ft_strlen(beg);
			s->len = 0;
			s->buf[0] = '\0';
			while (ST_OK(ft_src_peek(src, &c, 0)))
			{
				ft_dstr_pushc(s, c);
				if (c == '\n' && s->len >= l + 2 && s->buf[s->len - (l + 2)] == '\n')
				{
					if (ft_strncmp(s->buf + s->len - (l + 1), beg, l) != 0)
						continue ;
					ft_src_next(src, NULL, 1);
					ft_dstr_popn(s, l + 1, NULL);
					break ;
				}
				ft_src_next(src, NULL, 1);
			}
			free(beg);
			tok->val = next->val;
			next->val = NULL;
			next->id = SH_TOK_SPACE;
		}
	}
	return (OK);
}

inline t_st	sh_eval(t_sh *self)
{
	t_tok		*tok;
	t_st		st;
	t_job		*prev;
	t_job		job;
	t_job		hdoc;

	if (ST_NOK(st = sh_reduce(self)))
		return (st);
	prev = NULL;
	while (1)
	{
		if (!(tok = sh_next(self, NULL)))
			return (NOK);
		else if (ft_strchr(";\n", tok->id))
		{
			if (ft_vec_size(&self->worker))
			{
				if (ISE(st = ft_worker_run(&self->worker)))
					ft_putf(2, N_SH"%e", ST_TOENO(st));
				self->st = ft_worker_join(&self->worker);
			}
			sh_clean(self);
			if (tok->id == '\n')
				return (OK);
			prev = NULL;
		}
		else if (ft_strchr("\t ", tok->id))
			continue ;
		else if (tok->id == SH_TOK_PIPE)
		{
			if (!prev)
			{
				sh_consume_line(self);
				sh_clean(self);
				return (ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id));
			}
			ft_job_pipe(prev);
		}
		else if (tok->id == SH_TOK_RIN)
		{
			if (!prev)
			{
				sh_consume_line(self);
				sh_clean(self);
				return (ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id));
			}
			if (!(tok = sh_skip(self, "\t ")) || tok->id != SH_TOK_WORD)
			{
				sh_consume_line(self);
				sh_clean(self);
				return (tok ? ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id) : OK);
			}
			prev->in = ft_tok_ident(tok)->buf;
			sh_next(self, NULL);
		}
		else if (tok->id == SH_TOK_ROUT)
		{
			if (!prev)
			{
				sh_consume_line(self);
				sh_clean(self);
				return (ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id));
			}
			if (!(tok = sh_skip(self, "\t ")) || tok->id != SH_TOK_WORD)
			{
				sh_consume_line(self);
				sh_clean(self);
				return (tok ? ft_retf((self->st = 1) & 0,
					N_SH"Unexpected token '%c'\n", tok->id) : OK);
			}
			prev->out = ft_tok_ident(tok)->buf;
			sh_next(self, NULL);
		}
		else if (tok->id == SH_TOK_HEREDOC)
		{
			ft_job_output(&job, ft_tok_ident(tok)->buf);
			if (!(prev = ft_worker_push(&self->worker, &job)))
				return (ENO);
			continue ;
		}
		else if (ISE(st = sh_eval_bi(self, &job, tok)))
			return (st);
		else if (ST_OK(st))
		{
			if (!(prev = ft_worker_push(&self->worker, &job)))
				return (ENO);
			ft_job_data(prev, self);
			continue ;
		}
		else if (ISE(st = sh_eval_job(self, &job, tok)))
			return (st);
		else if (ST_OK(st))
		{
			sh_skip(self, "\t ");
			if ((tok = sh_peek(self)) && tok->id == SH_TOK_HEREDOC)
			{
				sh_next(self, NULL);
				ft_job_output(&hdoc, ft_tok_ident(tok)->buf);
				if (!(prev = ft_worker_push(&self->worker, &hdoc)))
					return (ENO);
				ft_job_pipe(prev);
			}
			if (!(prev = ft_worker_push(&self->worker, &job)))
				return (ENO);
			ft_job_data(prev, self);
			continue ;
		}
		else if (sh_peek(self) == tok)
		{
			sh_consume_line(self);
			sh_clean(self);
			return (ft_retf((self->st = 1) & 0,
				N_SH"Unexpected token '%c'\n", tok->id));
		}
		else
			self->st = st;
	}
}
