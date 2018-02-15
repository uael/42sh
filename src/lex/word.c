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
#define M(p, c) (s[p] == (c))

static inline uint8_t	wordid(char const *s, size_t l)
{
	if (l == 2 && M(0, 'i') && M(1, 'f'))
		return (TOK_IF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 'i') && M(3, 'f'))
		return (TOK_ELIF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 's') && M(3, 'e'))
		return (TOK_ELSE);
	if (l == 4 && M(0, 't') && M(1, 'h') && M(2, 'e') && M(3, 'n'))
		return (TOK_THEN);
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? TOK_FI : TOK_WORD));
}

static inline int		quote(int fd, t_tok *tok, char **it, char **ln)
{
	char	q;
	int		st;
	int		bs;

	bs = 0;
	st = 0;
	(void)(++tok->len && (q = *(*it)++));
	while (!st)
		if (!bs && q == '"' && (st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it)) || !**it))
			return (LEX_SHOWE(st, fd) ? sh_synerr(*ln, *it, UEC, q) : OUF);
		else if (bs && q != '\'')
			(void)((++tok->len && ++*it) && (bs = 0));
		else if (**it == q && (++tok->len && ++*it))
			break ;
		else if (!(bs = **it == '\\') && q == '"' && **it == '`')
			st = quote(fd, tok, it, ln);
		else if (q == '"' && **it == '$' && *(*it + 1) &&
			!ft_isspace(*(*it + 1)) && !ft_strchr(sh_varifs(), *(*it + 1)))
			st = sh_lexvar(fd, tok, it, ln);
		else
			(void)(++tok->len && ++*it);
	return (st);
}

inline int				sh_lexword(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;
	int		bs;

	st = 0;
	bs = 0;
	while (**it && !st)
		if (!bs && (ft_isspace(**it) || ft_strchr("><&|!;()", **it) ||
			(st = sh_lexbslash(fd, it, ln))))
			break ;
		else if (bs)
			(void)((++tok->len && ++*it) && (bs = 0));
		else if (!(bs = **it == '\\') && ISQUOTE(*it))
			st = quote(fd, tok, it, ln);
		else if (**it == '$' && *(*it + 1) && !ft_isspace(*(*it + 1)) &&
			!ft_strchr(sh_varifs(), *(*it + 1)))
			st = sh_lexvar(fd, tok, it, ln);
		else
			(void)(++tok->len && ++*it);
	if (st || !tok->len)
		return (st ? st : NOP);
	tok->id = wordid(*ln + tok->pos, tok->len);
	return (st);
}
