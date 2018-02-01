/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/reduce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define UEH "syntax error: Expected `%s' after heredoc `%s' got `%s'"
#define EXS "syntax error: Unexpected empty command between `%s'"

inline int		sh_lexreduce(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok *tok;
	t_tok *prev;
	t_tok *end;

	prev = NULL;
	tok = (t_tok *)ft_deqbeg(toks) - 1;
	end = ft_deqend(toks);
	while (++tok < end && tok->id != TOK_EOL && tok->id != TOK_END)
	{
		if (TOK_ISWORD(tok->id) && prev)
		{
			if (prev->id == TOK_HEREDOC && sh_lexheredoc(fd, tok, it, ln))
				return (OUF);
			if (prev->id == TOK_HEREDOCT && sh_lexheredoct(fd, tok, it, ln))
				return (OUF);
		}
		else if (prev && (prev->id == TOK_HEREDOC || prev->id == TOK_HEREDOCT))
			return (sh_synerr(*ln, *ln + tok->pos, UEH, sh_tokstr(tok),
			sh_tokidstr(prev->id), sh_tokidstr(tok->id)));
		else if (prev && prev->id == tok->id && TOK_ISSEP(tok->id))
			return (sh_synerr(*ln, *ln + tok->pos, EXS, sh_tokstr(tok)));
		prev = tok;
	}
	return (YEP);
}

inline char		sh_rbracket(char b)
{
	if (b == '[')
		return (']');
	if (b == '{')
		return ('}');
	if (b == '(')
		return (')');
	if (b == '`')
		return ('`');
	return (0);
}

inline t_bool	sh_isname(char *word)
{
	if (!ft_isalpha(*word) && *word != '_')
		return (0);
	++word;
	while (*word && *word != '=')
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (0);
		++word;
	}
	return (1);
}
