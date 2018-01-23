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
	if (l == 4 && M(0, 't') && M(1, 'r') && M(2, 'u') && M(3, 'e'))
		return (TOK_TRUE);
	if (l == 5 && M(0, 'f') && M(1, 'a') && M(2, 'l') && M(3, 's') && M(4, 'e'))
		return (TOK_FALSE);
	return (TOK_WORD);
}

inline int				sh_lexword(int fd, t_tok *tok, char **it, char **ln)
{
	char	*beg;
	int		st;

	beg = *it;
	st = 0;
	while (**it && !st)
		if (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it))
			break ;
		else if ((**it == '\'' || **it == '"'))
			st = sh_lexquote(fd, tok, it, ln);
		else if (**it == '\\' && ((*(*it + 1) == '\n' && !*(*it + 2)) ||
			(*(*it + 1) == '\r' && *(*it + 2) == '\n' && !*(*it + 3))))
		{
			*it += (*(*it + 1) == '\n') ? 2 : 3;
			fd >= 0 ? (st = rl_catline(fd, -2, ln, it)) : 0;
		}
		else if (**it == '$')
			st = sh_lexvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	if (st || (!tok->len && beg == *it))
		return (st ? st : NOP);
	if ((tok->id = wordid(tok->val, tok->len)) == TOK_WORD)
		sh_wordglob((t_sds *)tok);
	return (YEP);
}
