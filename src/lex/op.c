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

static inline int	opm(t_tok *tok, char **it, uint8_t len, uint8_t id)
{
	tok->id = id;
	ft_sdsmpush((t_sds *)tok, *it - len, len);
	return (YEP);
}

static inline int	opnext(int fd, char **it, char **ln)
{
	if (*++*it == '\\' && *++*it == '\n' && !*++*it &&
		(fd < 0 || !(*it = rl_catline(fd, "> ", -2, ln))))
		return (*it < (char *)0 ? WUT : NOP);
	return (YEP);
}

static inline int	opright(int fd, t_tok *tok, char **it, char **ln)
{
	if (opnext(fd, it, ln))
		return (WUT);
	if (**it == '>' && ++*it)
		return (opm(tok, it, 2, TOK_RAOUT));
	if (**it == '&' && ++*it)
		return (opm(tok, it, 2, TOK_RAMP));
	if (**it == '|' && ++*it)
		return (opm(tok, it, 2, TOK_RPOUT));
	return (opm(tok, it, 1, '>'));
}

static inline int	opleft(int fd, t_tok *tok, char **it, char **ln)
{
	if (opnext(fd, it, ln))
		return (WUT);
	if (**it == '<')
	{
		if (opnext(fd, it, ln))
			return (WUT);
		if (**it == '-' && ++*it)
			return (opm(tok, it, 3, TOK_HEREDOCT));
		return (opm(tok, it, 2, TOK_HEREDOC));
	}
	if (**it == '>' && ++*it)
		return (opm(tok, it, 2, TOK_CMP));
	if (**it == '&' && ++*it)
		return (opm(tok, it, 2, TOK_LAMP));
	return (opm(tok, it, 1, '<'));
}

inline int			sh_lexop(int fd, t_tok *tok, char **it, char **ln)
{
	if (**it == '>')
		return (opright(fd, tok, it, ln));
	if (**it == '<')
		return (opleft(fd, tok, it, ln));
	if (tok->len)
		return (NOP);
	if (**it == '&')
	{
		if (opnext(fd, it, ln))
			return (WUT);
		if (**it == '&' && ++*it)
			return (opm(tok, it, 2, TOK_LAND));
		if (**it == '>' && ++*it)
			return (opm(tok, it, 2, TOK_AMPR));
		return (opm(tok, it, 1, '&'));
	}
	if (**it == '|')
	{
		if (opnext(fd, it, ln))
			return (WUT);
		if (**it == '|' && ++*it)
			return (opm(tok, it, 2, TOK_LOR));
		return (opm(tok, it, 1, '|'));
	}
	return (ft_strchr("!;(){}", **it) ? opm(tok, it, 1, (uint8_t)*(*it)++) : 1);
}
