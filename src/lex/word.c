/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/shell.h"

#define ISQUOTE(IT) (*(IT) == '\'' || *(IT) == '"' || *(IT) == '`')
#define UEC "parse error: Unexpected EOF while looking for matching `%c'"

static inline int	quote(t_src *s, t_tok *tok, char q)
{
	int		st;
	int		bs;

	bs = 0;
	st = 0;
	(void)(++tok->len && (q = *(*s->it)++));
	while (!st)
		if (!bs && q == '"' && (st = sh_lexbslash(s)))
			return (st);
		else if (!**s->it && (s->fd < 0 ||
			(st = rl_catline(s->fd, 0, s->ln, s->it)) || !**s->it))
			return (LEXE(st, s->fd) ? sh_synerr(*s->ln, *s->it, UEC, q) : OUF);
		else if (bs && q != '\'')
			(void)((++tok->len && ++*s->it) && (bs = 0));
		else if (**s->it == q && (++tok->len && ++*s->it))
			break ;
		else if (!(bs = **s->it == '\\') && q == '"' && **s->it == '`')
			st = quote(s, tok, 0);
		else if (q == '"' && **s->it == '$' && *(*s->it + 1) &&
			!ft_isspace(*(*s->it + 1)) && !ft_strchr(sh_ifs(), *(*s->it + 1)))
			st = sh_lexdollar(s, tok);
		else
			(void)(++tok->len && ++*s->it);
	return (st);
}

inline int			sh_lexword(t_src *s, t_tok *tok)
{
	int		st;
	int		bs;

	st = 0;
	bs = 0;
	while (**s->it && !st)
		if (!bs && (ft_isspace(**s->it) || ft_strchr("><&|;()", **s->it) ||
			(st = sh_lexbslash(s))))
			break ;
		else if (bs)
			(void)((++tok->len && ++*s->it) && (bs = 0));
		else if (!(bs = **s->it == '\\') && ISQUOTE(*s->it))
			st = quote(s, tok, 0);
		else if (**s->it == '$' && *(*s->it + 1) &&
			!ft_isspace(*(*s->it + 1)) &&
			!ft_strchr(sh_ifs(), *(*s->it + 1)))
			st = sh_lexdollar(s, tok);
		else
			(void)(++tok->len && ++*s->it);
	if (st || !tok->len)
		return (st ? st : NOP);
	tok->id = TOK_WORD;
	return (st);
}
