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

#define UEE "parse error: Unexpected EOF while looking for heredoc delimiter "

static inline int	heredoc(t_tok *tok, char *eof, char **it, char **ln)
{
	size_t eofl;

	eofl = ft_strlen(eof);
	++tok->len;
	if ((!**it || ISEOL(*it)) && (tok->len == eofl + 1 ||
		(tok->len > eofl && ISREOL(*ln + tok->pos + tok->len - (eofl + 2)))) &&
		!ft_strncmp(*ln + tok->pos + tok->len - (eofl + 1), eof, eofl))
	{
		tok->len -= eofl + ISREOL(*it);
		++*it;
		return (YEP);
	}
	++*it;
	return (NOP);
}

inline int			sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	int		st;

	eof = ft_strndup(*ln + tok->pos, tok->len);
	tok->len = 0;
	tok->pos = (uint16_t)(*it - *ln);
	st = 0;
	while (!st)
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			st = st < 0 || !g_sh->tty ?
				sh_synerr(*ln, *it, UEE"`%s'", eof) : OUF;
		else
		{
			if (ISWEOL(*it))
				++*it;
			if (!heredoc(tok, eof, it, ln))
				break ;
		}
	free(eof);
	return (st);
}

inline int			sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	int		st;

	eof = ft_strndup(*ln + tok->pos, tok->len);
	tok->len = 0;
	tok->pos = (uint16_t)(*it - *ln);
	st = 0;
	while (!st)
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			st = st < 0 || !g_sh->tty ?
				sh_synerr(*ln, *it, UEE"`%s'", eof) : OUF;
		else
		{
			if (ISWEOL(*it))
				++*it;
			if (*it == *ln || (*(*it - 1) == '\n'))
				while (**it == '\t')
					++*it;
			if (!heredoc(tok, eof, it, ln))
				break ;
		}
	free(eof);
	return (st);
}
