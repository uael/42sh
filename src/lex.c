/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 08:03:29 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define M(p, c) (s[p] == (c))
#define W MSH_TOK_WORD
#define TOK(T) MSH_TOK_ ## T
#define MATCH(tok, src, n, id) ft_lexer_match(tok, src, n, id)

static inline t_ret		msh_lex_syntax(t_tok *tok, char peek, t_src *src)
{
	char	b[3];
	char	*c;
	ssize_t	n;

	n = 0;
	if ((b[n++] = peek) != '\n')
		while (n < 3 && ft_src_peek(src, b + n, (size_t)n) == RET_OK)
			if (b[n++] == '\n')
				break ;
	if (n == 3 && b[0] == '>' && b[1] == '>' && b[2] == '-')
		return (MATCH(tok, src, 3, MSH_TOK_RARROW));
	if (n >= 2 && b[1] == '>' && (b[0] == '>' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RSHIFT) : TOK(AMPR)));
	if (n >= 2 && b[0] == '>' && b[1] == '&')
		return (MATCH(tok, src, 2, MSH_TOK_RAMP));
	if (n >= 2 && b[1] == '|' && (b[0] == '>' || b[0] == '|'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RPIPE) : TOK(LOR)));
	if (n >= 2 && b[0] == '<' && (b[1] == '>' || b[1] == '<'))
		return (MATCH(tok, src, 2, b[1] == '>' ? TOK(CMP) : TOK(LSHIFT)));
	if (n >= 2 && b[1] == '&' && (b[0] == '<' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '<' ? TOK(LAMP ): TOK(LAND)));
	if (n >= 1 && (c = ft_strchr("=\t\n !&()-;<=>[]{|}", peek)))
		return (MATCH(tok, src, 1, (uint8_t)*c));
	return (RET_NOK);
}

static inline uint8_t	msh_keyword(char const *s, size_t l)
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
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? MSH_TOK_FI : W));
}

static inline t_ret		msh_isletter(char peek, t_src *src, t_bool *kw)
{
	if (peek != '\\')
	{
		if (ft_strchr("|&;<>()$`\\\"' \n\t", peek) == NULL)
		{
			if (!ft_isalpha(peek))
				*kw = 0;
			return (RET_OK);
		}
		return (RET_NOK);
	}
	*kw = 0;
	if (ft_src_peek(src, &peek, 1) == RET_OK && peek == '\n')
	{
		if (ft_src_next(src, NULL, 2) < 0 || ft_src_peek(src, &peek, 0) < 0)
			return (RET_ERR);
		return (msh_isletter(peek, src, kw));
	}
	if (!ft_strchr("|&;<>()$`\\\"' \n\t", peek))
		return (RET_NOK);
	if (ft_src_next(src, NULL, 1) < 0)
		return (RET_ERR);
	return (RET_OK);
}

static inline t_ret		msh_lex_word(t_tok *tok, char peek, t_src *src)
{
	t_dstr		*dstr;
	t_bool		kw;
	t_ret		r;

	kw = 1;
	ft_dstr_ctor(dstr = &tok->val->val.ident);
	while (peek && (r = msh_isletter(peek, src, &kw)) == 0)
		if (ft_src_next(src, &peek, 1) < 0 || !ft_dstr_pushc(dstr, peek))
			return (ft_dtor(RET_ERR, (t_dtor)ft_dstr_dtor, dstr, NULL));
		else if ((r = ft_src_peek(src, &peek, 0)) != 0)
			break ;
	if (r == RET_ERR)
		return (ft_dtor(RET_ERR, (t_dtor)ft_dstr_dtor, dstr, NULL));
	if (dstr->len == 0)
		return (ft_dtor(RET_NOK, (t_dtor)ft_dstr_dtor, dstr, NULL));
	if ((tok->id = kw ? msh_keyword(dstr->buf, dstr->len) : (uint8_t)W) == W)
		tok->val->kind = TOKV_IDENT;
	else
		ft_dstr_dtor(dstr, (void *)(tok->val = NULL));
	return (RET_OK);
}

inline t_ret			msh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (RET_ERR);
	*it = msh_lex_word;
	*(it + 1) = msh_lex_syntax;
	return (RET_OK);
}
