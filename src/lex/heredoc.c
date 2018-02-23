/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/shell.h"

#define UEE "parse error: Unexpected EOF while looking for heredoc delimiter"

static inline int	heredoc(t_src *s, t_tok *tok, char const *eof, size_t eofl)
{
	++tok->len;
	if ((!**s->it || ISEOL(*s->it)) && (tok->len == eofl + 1 ||
		(tok->len > eofl && ISREOL(*s->ln + tok->pos + tok->len - (eofl + 2))))
		&& !ft_strncmp(*s->ln + tok->pos + tok->len - (eofl + 1), eof, eofl))
	{
		tok->len -= eofl + ISREOL(*s->it);
		++*s->it;
		return (YEP);
	}
	++*s->it;
	return (NOP);
}

inline int			sh_lexheredoc(t_src *s, t_tok *tok)
{
	char	*eof;
	size_t	eofl;
	int		st;

	eof = ft_strndup(*s->ln + tok->pos, tok->len);
	eofl = tok->len;
	tok->len = 0;
	tok->pos = (uint16_t)(*s->it - *s->ln);
	st = 0;
	while (!st)
		if (!**s->it && (s->fd < 0 ||
			(st = rl_catline(s->fd, 0, s->ln, s->it))))
			st = LEXE(st, s->fd) ?
				sh_synerr(*s->ln, *s->it, UEE"`%s'", eof) : OUF;
		else if (!**s->it)
			break ;
		else
		{
			if (ISWEOL(*s->it))
				++*s->it;
			if (!heredoc(s, tok, eof, eofl))
				break ;
		}
	free(eof);
	return (st);
}
