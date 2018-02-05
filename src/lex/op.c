/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

static inline int	opright(int fd, t_tok2 *tok, char **it, char **ln)
{
	int st;

	if (++*it && (st = sh_lexbslash(fd, it, ln)))
		return (st);
	if (**it == '>' && ++*it)
		return ((tok->id = TOK_RAOUT) & 0);
	if (**it == '&' && ++*it)
		return ((tok->id = TOK_RAMP) & 0);
	if (**it == '|' && ++*it)
		return ((tok->id = TOK_RPOUT) & 0);
	return ((tok->id = '>') & 0);
}

static inline int	opleft(int fd, t_tok2 *tok, char **it, char **ln)
{
	int st;

	if (++*it && (st = sh_lexbslash(fd, it, ln)))
		return (st);
	if (**it == '<')
	{
		if (++*it && (st = sh_lexbslash(fd, it, ln)))
			return (st);
		if (**it == '-' && ++*it)
			return ((tok->id = TOK_HEREDOCT) & 0);
		return ((tok->id = TOK_HEREDOC) & 0);
	}
	if (**it == '>' && ++*it)
		return ((tok->id = TOK_CMP) & 0);
	if (**it == '&' && ++*it)
		return ((tok->id = TOK_LAMP) & 0);
	return ((tok->id = '<') & 0);
}

static inline int	opand(int fd, t_tok2 *tok, char **it, char **ln)
{
	int st;

	if (++*it && (st = sh_lexbslash(fd, it, ln)))
		return (st);
	if (**it == '&' && ++*it)
		return ((tok->id = TOK_LAND) & 0);
	if (**it == '>' && ++*it)
		return ((tok->id = TOK_AMPR) & 0);
	return ((tok->id = '&') & 0);
}

static inline int	opor(int fd, t_tok2 *tok, char **it, char **ln)
{
	int st;

	if (++*it && (st = sh_lexbslash(fd, it, ln)))
		return (st);
	if (**it == '|' && ++*it)
		return ((tok->id = TOK_LOR) & 0);
	return ((tok->id = '|') & 0);
}

inline int			sh_lexop(int fd, t_tok2 *tok, char **it, char **ln)
{
	if (**it == '>')
		return (opright(fd, tok, it, ln));
	if (**it == '<')
		return (opleft(fd, tok, it, ln));
	if (tok->len)
		return (NOP);
	if (**it == '&')
		return (opand(fd, tok, it, ln));
	if (**it == '|')
		return (opor(fd, tok, it, ln));
	return (ft_strchr(SYNCH, **it) ? (tok->id = *(uint8_t *)(*it)++) & 0 : 1);
}
