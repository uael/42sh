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

static inline int		inhib(t_tok *tok, char **it)
{
	ft_sdscpush((t_sds *)tok, **it != '$' ? *(*it)++ : (char)'\\');
	return (0);
}

inline int				sh_lexword(int fd, t_tok *t, char **it, char **ln)
{
	char	*beg;
	int		st;
	int		bs;

	beg = *it;
	ft_initf("%i%i", &st, &bs);
	while (**it && !st)
		if (!bs && (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it)))
			break ;
		else if (!bs && (st = sh_lexbslash(fd, it, ln)))
			break ;
		else if (bs)
			bs = inhib(t, it);
		else if ((bs = **it == '\\'))
			++*it;
		else if ((**it == '\'' || **it == '"'))
			st = sh_lexquote(fd, t, it, ln);
		else if (**it == '$' && (*it == *ln || *(*it - 1) != '\\'))
			st = sh_lexvar(fd, t, it, ln);
		else
			ft_sdscpush((t_sds *)t, *(*it)++);
	if (st || (!t->len && beg == *it))
		return (st ? st : NOP);
	(t->id = wordid(t->val, t->len)) == TOK_WORD ? sh_wordglob((t_sds *)t) : 0;
	return (YEP);
}
