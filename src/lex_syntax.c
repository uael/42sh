/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 12:37:20 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static inline uint8_t	msh_operator(char peek)
{
	if (peek == '=')
		return (MSH_TOK_ASSIGN);
	else if (peek == '!')
		return (MSH_TOK_NOT);
	else if (peek == '(')
		return (MSH_TOK_LPAR);
	else if (peek == ')')
		return (MSH_TOK_RPAR);
	else if (peek == '-')
		return (MSH_TOK_HYPEN);
	else if (peek == ';')
		return (MSH_TOK_SEMICOLON);
	else if (peek == '[')
		return (MSH_TOK_LBRACKET);
	else if (peek == ']')
		return (MSH_TOK_RBRACKET);
	else if (peek == '{')
		return (MSH_TOK_LCURLY);
	else if (peek == '}')
		return (MSH_TOK_RCURLY);
	else if (peek == ' ')
		return (MSH_TOK_SPACE);
	else if (peek == '\t')
		return (MSH_TOK_TAB);
	return ((uint8_t)(peek == '\n' ? MSH_TOK_EOL : 0));
}

static inline uint8_t	msh_redir_and(char peek, t_src *src)
{
	if (peek == '&')
	{
		if (ft_src_peek(src, 1) == '>')
			return (MSH_TOK_AMPR + (ft_src_next(src, NULL) & 0));
		else if (ft_src_peek(src, 1) == '&')
			return (MSH_TOK_LAND + (ft_src_next(src, NULL) & 0));
		return (MSH_TOK_AMP);
	}
	else if (peek == '|')
	{
		if (ft_src_peek(src, 1) == '|')
			return (MSH_TOK_LOR + (ft_src_next(src, NULL) & 0));
		return (MSH_TOK_PIPE);
	}
	return (msh_operator(peek));
}

static inline uint8_t	msh_redir(char peek, t_src *src)
{
	if (peek == '>')
	{
		if (ft_src_peek(src, 1) == '>')
		{
			if (ft_src_peek(src, 2) == '-' && ft_src_next(src, NULL) >= 0)
				return (MAH_TOK_RARROW + (ft_src_next(src, NULL) & 0));
			return (MSH_TOK_RSHIFT + (ft_src_next(src, NULL) & 0));
		}
		else if (ft_src_peek(src, 1) == '&')
			return (MSH_TOK_RAMP + (ft_src_next(src, NULL) & 0));
		else if (ft_src_peek(src, 1) == '|')
			return (MSH_TOK_RPIPE + (ft_src_next(src, NULL) & 0));
		return (MSH_TOK_GTH);
	}
	if (peek != '<')
		return (msh_redir_and(peek, src));
	if (ft_src_peek(src, 1) == '>')
		return (MSH_TOK_CMP + (ft_src_next(src, NULL) & 0));
	else if (ft_src_peek(src, 1) == '<')
		return (MSH_TOK_LSHIFT + (ft_src_next(src, NULL) & 0));
	else if (ft_src_peek(src, 1) == '&')
		return (MSH_TOK_LAMP + (ft_src_next(src, NULL) & 0));
	return (MSH_TOK_LTH);
}

inline int8_t			msh_lex_syntax(t_tok *tok, char peek, t_src *src)
{
	if (!(tok->id = msh_redir(peek, src)))
		return (1);
	ft_src_next(src, NULL);
	tok->val = NULL;
	return (0);
}
