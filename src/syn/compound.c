/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn/check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/syn.h"

#define ERR0 "syntax error: Expected `%s' after `%s' got `%s'"

static int	openerr(t_src *s, t_deq *toks, size_t const *idx, size_t open)
{
	t_tok	*tok;
	t_tok	*tok2;

	tok = ft_deqat(toks, open);
	tok2 = *idx >= toks->len ? NULL : ft_deqat(toks, *idx);
	return (sh_evalerr(*s->ln, tok2, ERR0,
		"<compound_list>", sh_tokstr(tok), sh_tokstr(tok2)));
}

static int	compoundlist(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	while (*idx < toks->len)
		if (((t_tok *)ft_deqat(toks, *idx))->id != '\n')
			break ;
		else
			++*idx;
	if ((st = sh_synterm(s, toks, idx)))
		return (st);
	if (*idx >= toks->len)
		return (YEP);
	tok = ft_deqat(toks, *idx);
	if (tok->id == '&' || tok->id == ';')
		++*idx;
	while (*idx < toks->len)
		if (((t_tok *)ft_deqat(toks, *idx))->id != '\n')
			break ;
		else
			++*idx;
	return (YEP);
}

inline int	sh_syncompoundlist(t_src *s, t_deq *toks, size_t *idx,
	char const *stop)
{
	int		st;
	size_t	open;

	open = (*idx)++;
	while (1)
		if (*idx >= toks->len)
		{
			if ((st = sh_lexline(s, toks, 1)))
				return (st != OUF ? openerr(s, toks, idx, open) : st);
		}
		else if ((st = compoundlist(s, toks, idx)) && st != NOP)
			return (st);
		else if (*idx >= toks->len)
			continue ;
		else if (ft_strchr(stop, ((t_tok *)ft_deqat(toks, *idx))->id))
			return (YEP);
		else
			return (openerr(s, toks, idx, open));
}

inline int	sh_syncompoundcmd(t_src *s, t_deq *toks, size_t *idx)
{
	int		st;
	t_tok	*tok;

	tok = ft_deqat(toks, *idx);
	if (tok->id == '{')
	{
		if ((st = sh_syncompoundlist(s, toks, idx, "}")))
			return (st);
		++*idx;
		return (YEP);
	}
	else if (tok->id == '(')
	{
		if ((st = sh_syncompoundlist(s, toks, idx, ")")))
			return (st);
		++*idx;
		return (YEP);
	}
	else if (tok->id == TOK_IF)
		return (sh_synifclause(s, toks, idx));
	else if (tok->id == TOK_WHILE)
		return (sh_synwhileclause(s, toks, idx));
	return (NOP);
}
