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

#define UEC "parse error: Unexpected EOF while looking for matching `%c'"

static inline uint8_t	wordid(char const *s, size_t l)
{
	char *eq;

	if (l == 1 && *s == '{')
		return ('{');
	if (l == 1 && *s == '}')
		return ('}');
	if (l == 1 && *s == '!')
		return ('!');
	if (l == 2 && !ft_strncmp("if", s, 2))
		return (TOK_IF);
	if (l == 2 && !ft_strncmp("[[", s, 2))
		return (TOK_DLBRA);
	if (l == 2 && !ft_strncmp("]]", s, 2))
		return (TOK_DRBRA);
	if (l == 2 && !ft_strncmp("fi", s, 2))
		return (TOK_FI);
	if (l >= 2 && !ft_strncmp("do", s, 2))
	{
		if (l == 2)
			return (TOK_DO);
		if (l < 4 || ft_strncmp("ne", s + 2, 2))
			return (TOK_WORD);
		return (TOK_DONE);
	}
	if (l == 4 && !ft_strncmp("elif", s, 4))
		return (TOK_ELIF);
	if (l == 4 && !ft_strncmp("else", s, 4))
		return (TOK_ELSE);
	if (l == 4 && !ft_strncmp("then", s, 4))
		return (TOK_THEN);
	if (l == 5 && !ft_strncmp("while", s, 5))
		return (TOK_WHILE);
	if (l == 8 && !ft_strncmp("function", s, 8))
		return (TOK_FUNCTION);
	if ((eq = ft_strnchr(s, '=', l)) && (eq > s) &&  sh_isident(s, eq - s))
		return (TOK_ASSIGN);
	return (TOK_WORD);
}

static inline int		quote(t_src *s, t_tok *tok, char q)
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

inline int				sh_lexword(t_src *s, t_tok *tok)
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
		else if (!(bs = **s->it == '\\') && ft_strchr("\"'`", **s->it))
			st = quote(s, tok, 0);
		else if (**s->it == '$' && *(*s->it + 1) &&
			!ft_isspace(*(*s->it + 1)) &&
			!ft_strchr(sh_ifs(), *(*s->it + 1)))
			st = sh_lexdollar(s, tok);
		else
			(void)(++tok->len && ++*s->it);
	if (st || !tok->len)
		return (st ? st : NOP);
	tok->id = wordid(*s->ln + tok->pos, tok->len);
	return (st);
}
