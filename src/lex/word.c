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
	ft_sdscpush((t_sds *)tok, *(*it)++);
	return (0);
}

static inline int		pushvar(int fd, t_tok **t, char **it, char **ln)
{
	int		st;
	t_tok	*prev;
	t_tok	*var;

	prev = *t;
	if (prev->id != TOK_VAR)
		prev->id = TOK_WORD;
	var = (*t)->len ? ft_deqpush(g_lextoks) : prev;
	var->len = 0;
	if ((*t)->len)
		var->spec |= TSPEC_CONTINUOUS;
	if (!(st = sh_lexvar(fd, var, it, ln)))
	{
		var->pos = prev->pos;
		if (!ft_isspace(**it) && !ft_strchr("><&|!;(){}", **it) &&
			!(st = sh_lexbslash(fd, it, ln)))
		{
			ft_sdsgrow((t_sds *)(*t = ft_deqpush(g_lextoks)), 1);
			(*t)->len = 0;
			(*t)->spec = 0;
			(*t)->spec |= TSPEC_CONTINUOUS;
			(*t)->pos = prev->pos;
		}
	}
	return (st);
}

static inline int		wordfini(int st, t_tok *t)
{
	if (st || !t->len)
	{
		t->spec = 0;
		return (st ? st : NOP);
	}
	if (t->id != TOK_VAR && !t->spec &&
		(t->id = wordid(t->val, t->len)) == TOK_WORD)
		sh_wordglob((t_sds *)t);
	else if (t->id != TOK_VAR)
		t->id = TOK_WORD;
	return (YEP);
}

inline int				sh_lexword(int fd, t_tok *t, char **it, char **ln)
{
	int		st;
	int		bs;

	ft_initf("%i%i", &st, &bs);
	while (**it && !st)
		if (!bs && (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it) ||
			(st = sh_lexbslash(fd, it, ln))))
			break ;
		else if (bs)
			bs = inhib(t, it);
		else if ((bs = **it == '\\'))
			++*it;
		else if ((**it == '\'' || **it == '"'))
			st = sh_lexquote(fd, &t, it, ln);
		else if (**it == '$' && *(*it + 1) && !ft_isspace(*(*it + 1)) &&
			!ft_strchr(sh_varifs(), *(*it + 1)))
			st = pushvar(fd, &t, it, ln);
		else
			ft_sdscpush((t_sds *)t, *(*it)++);
	return (wordfini(st, t));
}
