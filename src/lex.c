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

#include "ush/lex.h"

#define UNXPTD_C "Unexpected token `%c' while looking for matching `%c'"
#define UXPTD "Unexpected closing bracket `%c'"

static inline int	lexerhelp(int fd, char **i, char **ln)
{
	int st;

	*i += (*(*i + 1) == '\n') ? 2 : 3;
	if (fd >= 0 && (st = rl_catline(fd, -2, ln, i)) < 0)
		return (st);
	return (YEP);
}

static inline int	lexerhelp2(t_tok *tok, char **it, char **ln)
{
	tok->pos = (uint16_t)(*it - *ln);
	++*it;
	while (**it == '\n' || (**it == '\r' && *(*it + 1) == '\n'))
		++*it;
	tok->id = TOK_EOL;
	ft_sdscpush((t_sds *)tok, '\n');
	return (YEP);
}

static inline int	updatestack(t_tok *tok, char *stack, size_t *i, char **ln)
{
	if (ft_strchr("({[", tok->id))
		stack[(*i)++] = sh_isbracket(tok->id);
	else if (*i && tok->id == stack[*i - 1])
		--*i;
	else if (ft_strchr(")}]", tok->id) && (!*i || tok->id != stack[*i - 1]))
	{
		return (*i ? sh_synerr(*ln, *ln + tok->pos, UNXPTD_C, tok->id,
			stack[*i - 1]) : sh_synerr(*ln, *ln + tok->pos, UXPTD, tok->id));
	}
	return (YEP);
}

static inline int	lex(int f, t_tok *t, char **i, char **l)
{
	int s;

	t->len = 0;
	while (1)
		if (**i && ft_strchr(sh_varifs(), **i))
			++*i;
		else if (**i == '\n' || (**i == '\r' && *(*i + 1) == '\n'))
			return (lexerhelp2(t, i, l));
		else if (**i == '\\' && ((*(*i + 1) == '\n' && !*(*i + 2)) ||
			((*(*i + 1) == '\r' && *(*i + 2) == '\n' && !*(*i + 3)))))
		{
			if ((s = lexerhelp(f, i, l)))
				return (s);
		}
		else if (**i == '#')
			while (**i && (**i != '\n' || (**i != '\r' && *(*i + 1) != '\n')))
				++*i;
		else if (!**i && !(t->id = TOK_END))
			return ((t->pos = (uint16_t)(*i - *l)) & 0);
		else
			break ;
	t->pos = (uint16_t)(*i - *l);
	ft_isdigit(**i) ? ft_sdscpush((t_sds *)t, *(*i)++) : 0;
	return (s = sh_lexop(f, t, i, l)) != 1 || (s = sh_lexword(f, t, i, l)) != 1
		? s : sh_synerr(*l, *i, "Unexpected token `%c'", **i);
}

int					sh_lex(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok	*tok;
	int		st;
	char	stack[1000];
	size_t	i;

	if (!(i = 0) && !**it)
		return (NOP);
	!ln ? (ln = it) : 0;
	while ((tok = ft_deqpush(toks)) && ft_sdsgrow((t_sds *)tok, 1))
	{
		if (!(*tok->val = '\0') && !**it)
		{
			if (!i && !(tok->id = TOK_END))
				break ;
			if ((st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
				return (st);
		}
		if ((st = lex(fd, tok, it, ln)))
			return (st);
		if (!i && (tok->id == TOK_EOL || tok->id == TOK_END))
			break ;
		if (updatestack(tok, stack, &i, ln) == OUF)
			return (OUF);
	}
	return (tok ? sh_lexreduce(fd, toks, it, ln) : YEP);
}
