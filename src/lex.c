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

static inline uint8_t	msh_ident(char const *s, uint8_t l)
{
	if (l == 2 && M(0, 'i') && (M(1, 'f') || M(1, 'n')))
		return (M(1, 'f') ? MSH_TOK_KIF : MSH_TOK_KIN);
	if (M(0, 'd') && M(1, 'o') && (l == 2 || (l < 5 && M(2, 'n') && M(3, 'e'))))
		return (l == 2 ? MSH_TOK_KDO : MSH_TOK_DNE);
	if (l == 3 && M(0, 'f') && M(1, 'o') && M(2, 'r'))
		return (MSH_TOK_FOR);
	if (l == 4 && M(0, 'c') && M(1, 'a') && M(2, 's') && M(3, 'e'))
		return (MSH_TOK_CAS);
	if (l == 4 && M(0, 'e') && M(1, 's') && M(2, 'a') && M(3, 'c'))
		return (MSH_TOK_SAC);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 'i') && M(3, 'f'))
		return (MSH_TOK_EIF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 's') && M(3, 'e'))
		return (MSH_TOK_ELS);
	if (l == 4 && M(0, 't') && M(1, 'h') && M(2, 'e') && M(3, 'n'))
		return (MSH_TOK_THN);
	if (l == 5 && M(0, 'w') && M(1, 'h') && M(2, 'i') && M(3, 'l') && M(3, 'e'))
		return (MSH_TOK_WIL);
	if (l == 5 && M(0, 'u') && M(1, 'n') && M(2, 't') && M(3, 'i') && M(3, 'l'))
		return (MSH_TOK_UNT);
	if (l == 6 && ft_strcmp("select", s) == 0)
		return (MSH_TOK_SEL);
	if (l == 8 && ft_strcmp("function", s) == 0)
		return (MSH_TOK_FUN);
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? MSH_TOK_KFI : 0));
}

static inline int8_t	msh_lex_ident(t_tok *tok, char peek, t_src *src)
{
	char		buf[256];
	uint32_t	id;
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
	if (!(id = msh_ident(buf, len)))
		return ((int8_t)(ft_tokv_init_ident(tok->id.val, buf) ? 0 : -1));
	tok->is_id = 1;
	tok->id.id = id;
	return (0);
}

static inline int8_t	msh_lex_syntax(t_tok *tok, char peek, t_src *src)
{
	uint32_t id;

	id = tok->id.id;
	if (peek == ' ')
		tok->id.id = MSH_TOK_SPC + (ft_src_next(src) & 0);
	else if (peek == '\n')
		tok->id.id = MSH_TOK_EOL + (ft_src_next(src) & 0);
	return ((int8_t)(id != tok->id.id ? (tok->is_id = 1) & 0 : 1));
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
