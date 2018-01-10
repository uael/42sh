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

inline void			sh_tokdtor(t_tok *tok)
{
	if (tok->val)
		free(tok->val);
	FT_INIT(tok, t_tok);
}

static inline int	lex(int fd, t_tok *tok, char **it, char **ln)
{
	tok->len = 0;
	while (**it == ' ' || **it == '\t')
		++*it;
	if (**it == '\n')
	{
		tok->id = TOK_EOL;
		ft_sdscpush((t_sds *)tok, '\n');
		++*it;
		return (YEP);
	}
	if (**it == '\\' && *++*it == '\n' && !*++*it &&
		(fd < 0 || !(*it = sh_readcat(fd, "> ", -2, ln))))
		return (WUT);
	if (ft_isdigit(**it))
		ft_sdscpush((t_sds *)tok, *(*it)++);
	if (sh_lexop(fd, tok, it, ln) && sh_lexword(fd, tok, it, ln))
		return (ENO_THROW(WUT, EINVAL));
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
		prev = tok;
	}
	return (YEP);
}

/*
** TODO: parse heredoc once line is totaly parsed
** to work, the current algo requires things that
** the norme doesn't allow me to do..
*/

int					sh_lex(int fd, t_deq *toks, char *ln)
{
	t_tok	*tok;
	char	*beg;

	tok = NULL;
	toks->len = 0;
	toks->cur = 0;
	beg = ln;
	while (*ln)
	{
		if (lex(fd, tok = ft_deqpush(toks), &ln, &beg))
			return (WUT);
		if (tok->id == TOK_EOL)
			break ;
	}
	if (tok)
		return (reduce(fd, toks, &ln, &beg));
	return (YEP);
}
