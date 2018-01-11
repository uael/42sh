/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/lex.h"
#include "msh/err.h"

static inline int	lex(int fd, t_tok *tok, char **it, char **ln)
{
	int	st;

	tok->len = 0;
	while (**it == ' ' || **it == '\t')
		++*it;
	if (**it == '\n' || (**it == '\r' && *(*it + 1) == '\n'))
	{
		tok->id = TOK_EOL;
		ft_sdscpush((t_sds *)tok, '\n');
		while (*++*it == '\n')
			;
		return (YEP);
	}
	if (**it == '\\' && *++*it == '\n' && !*++*it &&
		(fd < 0 || !(*it = rl_catline(fd, "> ", -2, ln))))
		return (sh_errparse(*ln, *it, "Unexpected end of file after '\\'"));
	if (ft_isdigit(**it))
		ft_sdscpush((t_sds *)tok, *(*it)++);
	if ((st = sh_lexop(fd, tok, it, ln)) < 0)
		return (WUT);
	if (st && (st = sh_lexword(fd, tok, it, ln)) < 0)
		return (WUT);
	if (st)
		return (sh_errparse(*ln, *it, "Unexpected token '%c'", **it));
	return (YEP);
}

static inline int	reduce(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok	*tok;
	t_tok	*prev;
	t_tok	*end;

	prev = NULL;
	tok = (t_tok *)ft_deqbeg(toks) - 1;
	end = ft_deqend(toks);
	while (++tok < end)
	{
		if (tok->id == TOK_WORD && prev)
		{
			if (prev->id == TOK_HEREDOC && sh_lexheredoc(fd, tok, it, ln))
				return (WUT);
			if (prev->id == TOK_HEREDOCT && sh_lexheredoct(fd, tok, it, ln))
				return (WUT);
		}
		else if (prev && prev->id == TOK_HEREDOC)
			return (sh_errparse(*ln, *it, "Expected word after heredoc '<<'"));
		else if (prev && prev->id == TOK_HEREDOCT)
			return (sh_errparse(*ln, *it, "Expected word after heredoc '<<-'"));
		prev = tok;
	}
	return (YEP);
}

int					sh_lex(int fd, t_deq *toks, char *ln)
{
	t_tok	*tok;
	char	*beg;
	int 	st;

	tok = NULL;
	toks->len = 0;
	toks->cur = 0;
	beg = ln;
	st = 0;
	if (*ln)
		while ((tok = ft_deqpush(toks)))
		{
			if (!*ln)
			{
				tok->id = TOK_END;
				break ;
			}
			else if ((st = lex(fd, tok, &ln, &beg)) < 0)
				return (WUT);
			else if (st || tok->id == TOK_EOL)
				break ;
		}
	if (!st && tok)
		return (reduce(fd, toks, &ln, &beg));
	return (YEP);
}
