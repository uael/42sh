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
#define W SH_TOK_WORD
#define TOK(T) SH_TOK_ ## T
#define MATCH(tok, src, n, id) ft_lexer_match(tok, src, n, id)

inline t_st				sh_tok_syntax(t_tok *tok, char peek, t_src *src)
{
	char	b[3];
	char	*c;
	ssize_t	n;

	n = 0;
	if ((b[n++] = peek) != '\n')
		while (n < 3 && ST_OK(ft_src_peek(src, b + n, (size_t)n)))
			if (b[n++] == '\n')
				break ;
	if (n == 3 && b[0] == '>' && b[1] == '>' && b[2] == '-')
		return (MATCH(tok, src, 3, SH_TOK_RARROW));
	if (n >= 2 && b[1] == '>' && (b[0] == '>' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RSHIFT) : TOK(AMPR)));
	if (n >= 2 && b[0] == '>' && b[1] == '&')
		return (MATCH(tok, src, 2, SH_TOK_RAMP));
	if (n >= 2 && b[1] == '|' && (b[0] == '>' || b[0] == '|'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RPIPE) : TOK(LOR)));
	if (n >= 2 && b[0] == '<' && (b[1] == '>' || b[1] == '<'))
		return (MATCH(tok, src, 2, b[1] == '>' ? TOK(CMP) : TOK(LSHIFT)));
	if (n >= 2 && b[1] == '&' && (b[0] == '<' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '<' ? TOK(LAMP) : TOK(LAND)));
	if (n >= 1 && (c = ft_strchr("=\t\n !&()-;<=>[]{|}", peek)))
		return (MATCH(tok, src, 1, (uint8_t)*c));
	return (NOK);
}

static inline uint8_t	sh_keyword(char const *s, size_t l)
{
	if (l == 2 && M(0, 'i') && (M(1, 'f') || M(1, 'n')))
		return (M(1, 'f') ? SH_TOK_IF : SH_TOK_IN);
	if (M(0, 'd') && M(1, 'o') && (l == 2 || (l < 5 && M(2, 'n') && M(3, 'e'))))
		return (l == 2 ? SH_TOK_DO : SH_TOK_DONE);
	if (l == 3 && M(0, 'f') && M(1, 'o') && M(2, 'r'))
		return (SH_TOK_FOR);
	if (l == 4 && M(0, 'c') && M(1, 'a') && M(2, 's') && M(3, 'e'))
		return (SH_TOK_CASE);
	if (l == 4 && M(0, 'e') && M(1, 's') && M(2, 'a') && M(3, 'c'))
		return (SH_TOK_ESAC);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 'i') && M(3, 'f'))
		return (SH_TOK_ELIF);
	if (l == 4 && M(0, 'e') && M(1, 'l') && M(2, 's') && M(3, 'e'))
		return (SH_TOK_ELSE);
	if (l == 4 && M(0, 't') && M(1, 'h') && M(2, 'e') && M(3, 'n'))
		return (SH_TOK_THEN);
	if (l == 5 && M(0, 'w') && M(1, 'h') && M(2, 'i') && M(3, 'l') && M(3, 'e'))
		return (SH_TOK_WHILE);
	if (l == 5 && M(0, 'u') && M(1, 'n') && M(2, 't') && M(3, 'i') && M(3, 'l'))
		return (SH_TOK_UNTIL);
	if (l == 6 && ft_strcmp("select", s) == 0)
		return (SH_TOK_SELECT);
	if (l == 8 && ft_strcmp("function", s) == 0)
		return (SH_TOK_FUNCTION);
	return ((uint8_t)((l == 2 && M(0, 'f') && M(1, 'i')) ? SH_TOK_FI : W));
}

static inline t_st		sh_pp(char *peek, t_src *src, char *t)
{
	t_st	st;
	t_sz	sz;

	if ((*peek == '\'' || *peek == '\"') && (!*t || *t == *peek))
	{
		*t = (char)(*t ? '\0' : *peek);
		if ((st = ft_src_getc(src, NULL, peek)) != 0)
			return (st);
		return (sh_pp(peek, src, t));
	}
	if (!*t && *peek != '\\' && ft_strchr("|&;<>()$`\\\"' \n\t", *peek))
		return (NOK);
	else if (*peek != '\\')
		return (OK);
	if ((st = ft_src_peek(src, peek, 1)) != 0)
		return (st);
	if (*t && !ft_strchr(*t == '\"' ? "$`\"\\\n" : "'", *peek))
		return (NOK);
	if (!*t && !ft_strchr("|&;<>()$`\\\"' \n\t", *peek))
		return (NOK);
	return ((sz = ft_src_next(src, NULL, 1)) != 1 ? SZ_TOST(sz) : OK);
}

inline t_st				sh_tok_word(t_tok *tok, char peek, t_src *src)
{
	t_dstr		*dstr;
	t_st		st;
	char		t;

	t = '\0';
	ft_dstr_ctor(dstr = &tok->val->val.ident);
	while (peek && (st = sh_pp(&peek, src, &t)) == 0)
		if (!ft_dstr_pushc(dstr, peek))
			return (ft_dtor(ENO, (t_dtor)ft_dstr_dtor, dstr, NULL));
		else if (ST_NOK(st = ft_src_getc(src, NULL, &peek)))
			return (st);
	if (ISE(st) || dstr->len == 0)
		return (ft_dtor(ISE(st) ? st : NOK, (t_dtor)ft_dstr_dtor, dstr, NULL));
	if ((tok->id = sh_keyword(dstr->buf, dstr->len)) == W)
		tok->val->kind = TOKV_IDENT;
	else
		ft_dstr_dtor(dstr, (void *)(tok->val = NULL));
	return (OK);
}
