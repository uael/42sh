/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define M(p, c) (s[p] == (c))
#define WORD MSH_TOK_WORD

static inline uint8_t	msh_ident(char const *s, uint8_t l)
{
	if (l == 2 && M(0, 'i') && (M(1, 'f') || M(1, 'n')))
		return (M(1, 'f') ? MSH_TOK_IF : MSH_TOK_IN);
	if (M(0, 'd') && M(1, 'o') && (l == 2 || (l < 5 && M(2, 'n') && M(3, 'e'))))
		return (l == 2 ? MSH_TOK_DO : MSH_TOK_DONE);
	if (l == 3 && M(0, 'f') && M(1, 'o') && M(2, 'r'))
		return (MSH_TOK_FOR);
	if (l == 4 && M(0, 'c') && M(1, 'a') && M(2, 's') && M(3, 'e'))
		return (MSH_TOK_CASE);
	if (l == 4 && M(0, 'e') && M(1, 's') && M(2, 'a') && M(3, 'c'))
		return (MSH_TOK_ESAC);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 'i') && M(3, 'f'))
		return (MSH_TOK_ELIF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 's') && M(3, 'e'))
		return (MSH_TOK_ELSE);
	if (l == 4 && M(0, 't') && M(1, 'h') && M(2, 'e') && M(3, 'n'))
		return (MSH_TOK_THEN);
	if (l == 5 && M(0, 'w') && M(1, 'h') && M(2, 'i') && M(3, 'l') && M(3, 'e'))
		return (MSH_TOK_WHILE);
	if (l == 5 && M(0, 'u') && M(1, 'n') && M(2, 't') && M(3, 'i') && M(3, 'l'))
		return (MSH_TOK_UNTIL);
	if (l == 6 && ft_strcmp("select", s) == 0)
		return (MSH_TOK_SELECT);
	if (l == 8 && ft_strcmp("function", s) == 0)
		return (MSH_TOK_FUNCTION);
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? MSH_TOK_FI : WORD));
}

static inline int8_t	msh_lex_ident(t_tok *tok, char peek, t_src *src)
{
	char		buf[256];
	uint8_t		len;

	if (!ft_isalpha(peek))
		return (1);
	len = 0;
	buf[len++] = peek;
	peek = ft_src_next(src);
	while (ft_isalnum(peek))
	{
		buf[len++] = peek;
		peek = ft_src_next(src);
	}
	if (peek == '_')
	{
		buf[len++] = peek;
		ft_src_next(src);
	}
	buf[len] = '\0';
	if ((tok->id = msh_ident(buf, len)) == WORD)
		return ((int8_t)(ft_tokv_init_ident(tok->val, buf) ? 0 : -1));
	tok->val = NULL;
	return (0);
}

static inline int8_t	msh_lex_syntax(t_tok *tok, char peek, t_src *src)
{
	if (peek == '>')
	{
		if (ft_src_peek(src, 1) == '>')
		{
			if (ft_src_peek(src, 2) == '-' && ft_src_next(src) >= 0)
				tok->id = MAH_TOK_RARROW + (ft_src_next(src) & 0);
			else
				tok->id = MSH_TOK_RSHIFT + (ft_src_next(src) & 0);
		}
		else if (ft_src_peek(src, 1) == '&')
			tok->id = MSH_TOK_RAMP + (ft_src_next(src) & 0);
		else if (ft_src_peek(src, 1) == '|')
			tok->id = MSH_TOK_RPIPE + (ft_src_next(src) & 0);
		else
			tok->id = MSH_TOK_GTH;
	}
	else if (peek == '<')
	{
		if (ft_src_peek(src, 1) == '>')
			tok->id = MSH_TOK_CMP + (ft_src_next(src) & 0);
		else if (ft_src_peek(src, 1) == '<')
			tok->id = MSH_TOK_LSHIFT + (ft_src_next(src) & 0);
		else if (ft_src_peek(src, 1) == '&')
			tok->id = MSH_TOK_LAMP + (ft_src_next(src) & 0);
		else
			tok->id = MSH_TOK_LTH;
	}
	else if (peek == '&')
	{
		if (ft_src_peek(src, 1) == '>')
			tok->id = MSH_TOK_AMPR + (ft_src_next(src) & 0);
		else if (ft_src_peek(src, 1) == '&')
			tok->id = MSH_TOK_LAND + (ft_src_next(src) & 0);
		else
			tok->id = MSH_TOK_AMP;
	}
	else if (peek == '|')
	{
		if (ft_src_peek(src, 1) == '|')
			tok->id = MSH_TOK_LOR + (ft_src_next(src) & 0);
		else
			tok->id = MSH_TOK_PIPE;
	}
	else if (peek == '=')
		tok->id = MSH_TOK_ASSIGN;
	else if (peek == '!')
		tok->id = MSH_TOK_NOT;
	else if (peek == '(')
		tok->id = MSH_TOK_LPAR;
	else if (peek == ')')
		tok->id = MSH_TOK_RPAR;
	else if (peek == '-')
		tok->id = MSH_TOK_HYPEN;
	else if (peek == ';')
		tok->id = MSH_TOK_SEMICOLON;
	else if (peek == '[')
		tok->id = MSH_TOK_LBRACKET;
	else if (peek == ']')
		tok->id = MSH_TOK_RBRACKET;
	else if (peek == '{')
		tok->id = MSH_TOK_LCURLY;
	else if (peek == '}')
		tok->id = MSH_TOK_RCURLY;
	else if (peek == ' ')
		tok->id = MSH_TOK_SPACE;
	else if (peek == '\t')
		tok->id = MSH_TOK_TAB;
	else if (peek == '\n')
		tok->id = MSH_TOK_EOL;
	else if (peek == '\\')
		tok->id = MSH_TOK_LSLASH;
	return (tok->id && ft_src_next(src) >= 0 ?
		(int8_t)(tok->val = NULL) : (int8_t)1);
}

extern t_bool			msh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (0);
	*it = msh_lex_syntax;
	*(it + 1) = msh_lex_ident;
	return (1);
}
