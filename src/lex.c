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
#include "ush/tok.h"

#define UXTDC "Unexpected token `%c' while looking for matching `%c'"
#define UXTDE "Unexpected EOF while looking for matching `%c'"
#define UXTD "Unexpected closing bracket `%c'"

static char			g_stack[1000] = { 0 };
static int			g_stack_idx;

static inline int	lexone(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;

	while (1)
		if ((st = sh_lexbquote(fd, it, ln)))
			return (st);
		else if (**it && ft_strchr(sh_varifs(), **it))
			++*it;
		else if (ISEOL(*it))
		{
			sh_tokpos(tok, ++*it, *ln)->id = TOK_EOL;
			ft_sdscpush((t_sds *)tok, '\n');
			return (YEP);
		}
		else if (**it == '#')
			while (**it && !ISEOL(*it))
				++*it;
		else if (!**it)
			return (sh_tokpos(tok, *it, *ln)->id = TOK_END);
		else
			break ;
	sh_tokpos(tok, *it, *ln);
	ft_isdigit(**it) ? ft_sdscpush((t_sds *)tok, *(*it)++) : 0;
	return (st = sh_lexop(fd, tok, it, ln)) != NOP ||
		(st = sh_lexword(fd, tok, it, ln)) != NOP
		? st : sh_synerr(*ln, *it, "Unexpected token `%c'", **it);
}

static inline int	lexline(int fd, t_deq *toks, char **it, char **ln)
{
	int		st;
	t_tok	*tok;

	!ln ? (ln = it) : 0;
	while (1)
	{
		ft_sdsgrow((t_sds *)(tok = ft_deqpush(toks)), 1);
		*tok->val = '\0';
		tok->len = 0;
		if ((st = lexone(fd, tok, it, ln)))
			return (st);
		if (tok->id == TOK_EOL || tok->id == TOK_END)
			break ;
		if (ft_strchr("([{", tok->id))
			g_stack[g_stack_idx++] = sh_rbracket(tok->id);
		else if (g_stack_idx && tok->id == g_stack[g_stack_idx - 1])
			--g_stack_idx;
		else if (ft_strchr(")}]", tok->id) &&
			(!g_stack_idx || tok->id != g_stack[g_stack_idx - 1]))
			return (g_stack_idx ? sh_synerr(*ln, *ln + tok->pos, UXTDC, tok->id,
				g_stack[g_stack_idx - 1]) : sh_synerr(*ln, *ln + tok->pos, UXTD,
				tok->id));
	}
	return (YEP);
}

int					sh_lex(int fd, t_deq *toks, char **it, char **ln)
{
	int		st;
	size_t	sve;
	size_t	cur;

	if (!**it)
		return (NOP);
	g_stack_idx = 0;
	sve = toks->cur;
	while (1)
	{
		cur = toks->len;
		if ((st = lexline(fd, toks, it, ln)))
			return (st);
		toks->cur = cur;
		if ((st = sh_lexreduce(fd, toks, it, ln)))
			return (st);
		toks->cur = sve;
		if (!g_stack_idx)
			return (YEP);
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || fd != 0 ?
				sh_synerr(*ln, *it, UXTDE, g_stack[g_stack_idx - 1]) : OUF);
	}
}
