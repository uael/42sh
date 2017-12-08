/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce/heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 12:12:33 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static t_st heredoc_rd(t_src *src, t_dstr *hdoc, char *eof)
{
	char	c;
	size_t	l;
	t_st	st;
	t_sz	sz;

	l = ft_strlen(eof);
	while (ST_OK(st = ft_src_peek(src, &c, 0)))
	{
		if (!ft_dstr_pushc(hdoc, c))
			return (ENO);
		if (c == '\n' && hdoc->len >= l + 2 &&
			hdoc->buf[hdoc->len - (l + 2)] == '\n')
		{
			if (ft_strncmp(hdoc->buf + hdoc->len - (l + 1), eof, l) != 0)
				continue ;
			if (ISE(sz = ft_src_next(src, NULL, 1)))
				return (SZ_TOST(sz));
			ft_dstr_popn(hdoc, l + 1, NULL);
			break ;
		}
		if (ISE(sz = ft_src_next(src, NULL, 1)))
			return (SZ_TOST(sz));
	}
	return (ISE(st) ? st : 0);
}

t_st		sh_reduce_heredoc(t_sh *self, t_tok *tok)
{
	t_tok	*next;
	t_dstr	*hdoc;
	char	*eof;
	t_src	*src;
	t_st	st;

	if ((next = tok + 1) == ft_deq_end(&self->lexer.toks) ||
		next->id != SH_TOK_WORD)
		return (ft_retf((self->st = 1) & 0,
			N_SH"Unexpected token '%c'\n", tok->id));
	if (ft_deq_size(&self->lexer.srcs) == 0 ||
		!(src = ft_deq_at(&self->lexer.srcs, 0)))
		return (ft_retf((self->st = 1) & 0,
			N_SH"Unexpected token '%c'\n", tok->id));
	hdoc = ft_tokv_ident(next->val);
	if (!(eof = ft_strdup(hdoc->buf)))
		return (ENO);
	hdoc->len = 0;
	hdoc->buf[0] = '\0';
	if (ISE(st = heredoc_rd(src, hdoc, eof)))
		return (st);
	free(eof);
	tok->val = next->val;
	next->val = NULL;
	next->id = SH_TOK_SPACE;
	return (OK);
}
