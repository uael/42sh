/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce/heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static int	heredoc_rd(t_lexer *src, t_dstr *hdoc, char *eof)
{
	char	c;
	size_t	l;
	int		st;

	l = ft_strlen(eof);
	while ((st = ft_lexer_peek(src, &c, 0)) == YEP)
	{
		ft_dstr_pushc(hdoc, c);
		if (c == '\n' && hdoc->len >= l + 2 &&
			hdoc->buf[hdoc->len - (l + 2)] == '\n')
		{
			if (ft_strncmp(hdoc->buf + hdoc->len - (l + 1), eof, l) != 0)
				continue ;
			if (ft_lexer_next(src, NULL, 1) < 0)
				return (WUT);
			ft_dstr_popn(hdoc, l + 1, NULL);
			break ;
		}
		if (ft_lexer_next(src, NULL, 1) < 0)
			return (WUT);
	}
	return (st);
}

int			sh_reduce_heredoc(t_sh *self, t_tok *tok)
{
	t_tok	*next;
	t_dstr	*hdoc;
	char	*eof;
	int		st;

	if ((next = tok + 1) == ft_deq_end(&self->lexer.toks) ||
		next->id != SH_TOK_WORD)
		return (ft_retf(NOP, N_SH"Syntax error '%c'\n", tok->id));
	hdoc = ft_tokv_ident(next->val);
	eof = ft_strdup(hdoc->buf);
	hdoc->len = 0;
	hdoc->buf[0] = '\0';
	st = heredoc_rd(&self->lexer, hdoc, eof);
	free(eof);
	if (st)
		return (st < 0 ? st : ft_retf(NOP, N_SH"Syntax error '%c'\n", tok->id));
	next->id = SH_TOK_SKIP;
	return (YEP);
}
