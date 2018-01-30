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

#define UEE "parse error: Unexpected EOF while looking for heredoc delimiter "

static inline int	heredoc(t_tok *tok, char *eof, size_t eofl, char **it)
{
	ft_sdscpush((t_sds *)tok, **it);
	if ((!**it || ISEOL(*it)) && (tok->len == eofl + 1 ||
		(tok->len > eofl && ISREOL(tok->val + tok->len - (eofl + 2)))) &&
		!ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
	{
		ft_sdsnpop((t_sds *)tok, eofl + ISREOL(*it), NULL);
		return (YEP);
	}
	++*it;
	return (NOP);
}

inline int			sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;
	int		st;

	eofl = tok->len;
	eof = ft_memdup(tok->val, (tok->len + 1) * sizeof(char));
	tok->len = 0;
	st = 0;
	while (!st)
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			st = st < 0 || fd != 0 ? sh_synerr(*ln, *it, UEE"`%s'", eof) : OUF;
		else
		{
			if (ISWEOL(*it))
				++*it;
			if (!heredoc(tok, eof, eofl, it))
				break ;
		}
	free(eof);
	return (st);
}

inline int			sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eof;
	size_t	eofl;
	int		st;

	eofl = tok->len;
	eof = ft_memdup(tok->val, (tok->len + 1) * sizeof(char));
	tok->len = 0;
	st = 0;
	while (!st)
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			st = st < 0 || fd != 0 ? sh_synerr(*ln, *it, UEE"`%s'", eof) : OUF;
		else
		{
			if (ISWEOL(*it))
				++*it;
			if (*it == *ln || (*(*it - 1) == '\n'))
				while (**it == '\t')
					++*it;
			if (!heredoc(tok, eof, eofl, it))
				break ;
		}
	free(eof);
	return (st);
}
