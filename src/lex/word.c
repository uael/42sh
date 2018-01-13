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

#define M(p, c) (s[p] == (c))

static inline uint8_t	wordid(char const *s, size_t l)
{
	if (l == 2 && M(0, 'i') && (M(1, 'f') || M(1, 'n')))
		return (M(1, 'f') ? TOK_IF : TOK_IN);
	if (M(0, 'd') && M(1, 'o') && (l == 2 || (l < 5 && M(2, 'n') && M(3, 'e'))))
		return (l == 2 ? TOK_DO : TOK_DONE);
	if (l == 3 && M(0, 'f') && M(1, 'o') && M(2, 'r'))
		return (TOK_FOR);
	if (l == 4 && M(0, 'c') && M(1, 'a') && M(2, 's') && M(3, 'e'))
		return (TOK_CASE);
	if (l == 4 && M(0, 'e') && M(1, 's') && M(2, 'a') && M(3, 'c'))
		return (TOK_ESAC);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 'i') && M(3, 'f'))
		return (TOK_ELIF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 's') && M(3, 'e'))
		return (TOK_ELSE);
	if (l == 4 && M(0, 't') && M(1, 'h') && M(2, 'e') && M(3, 'n'))
		return (TOK_THEN);
	if (l == 5 && M(0, 'w') && M(1, 'h') && M(2, 'i') && M(3, 'l') && M(4, 'e'))
		return (TOK_WHILE);
	if (l == 5 && M(0, 'u') && M(1, 'n') && M(2, 't') && M(3, 'i') && M(4, 'l'))
		return (TOK_UNTIL);
	if (l == 6 && ft_strcmp("select", s) == 0)
		return (TOK_SELECT);
	if (l == 8 && ft_strcmp("function", s) == 0)
		return (TOK_FUNCTION);
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? TOK_FI : TOK_WORD));
}

inline int				sh_lexword(int fd, t_tok *tok, char **it, char **ln)
{
	char *beg;

	beg = *it;
	while (**it)
		if (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it))
			break ;
		else if (**it == '\'' || **it == '"')
		{
			if (sh_lexquote(fd, tok, it, ln) < 0)
				return (WUT);
		}
		else if (**it == '\\' && *++*it == '\n' && !*++*it &&
			(fd < 0 || !(*it = rl_catline(fd, "> ", -2, ln))))
			return (*it == (char *)-1 ? WUT : NOP);
		else if (**it == '$')
		{
			if (sh_lexvar(fd, tok, it, ln) < 0)
				return (WUT);
		}
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	if (beg == *it)
		return (NOP);
	tok->id = wordid(tok->val, tok->len);
	return (YEP);
}
