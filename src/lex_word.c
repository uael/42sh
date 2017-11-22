/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 12:37:20 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define M(p, c) (s[p] == (c))
#define W MSH_TOK_WORD

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

static inline t_bool	msh_isletter(char peek, t_src *src, t_bool *kw)
{
	if (peek != '\\')
	{
		if (ft_strchr("|&;<>()$`\\\"' \n\t", peek) == NULL)
		{
			if (!ft_isalpha(peek))
				*kw = 0;
			return (1);
		}
		return (0);
	}
	*kw = 0;
	if ((peek = ft_src_peek(src, 1)) == '\n')
		return ((t_bool)(ft_src_nnext(src, 2, NULL) > 0));
	if (!ft_strchr("|&;<>()$`\\\"' \n\t", peek))
		return (0);
	return ((t_bool)(ft_src_next(src, NULL) > 0));
}

inline int8_t			msh_lex_word(t_tok *tok, char peek, t_src *src)
{
	t_dstr		*dstr;
	t_bool		kw;

	kw = 1;
	if (!msh_isletter(peek, src, &kw))
		return (1);
	ft_dstr_ctor(dstr = &tok->val->val.ident);
	if (!ft_dstr_pushc(dstr, ft_src_next(src, &peek)))
		return (ft_dtor(-1, (t_dtor)ft_dstr_dtor, dstr));
	while (msh_isletter(peek, src, &kw))
		if (!ft_dstr_pushc(dstr, ft_src_next(src, &peek)))
			return (ft_dtor(-1, (t_dtor)ft_dstr_dtor, dstr));
	if ((tok->id = kw ? msh_keyword(dstr->buf, dstr->len) : (uint8_t)W) == W)
		tok->val->kind = TOKV_IDENT;
	else
		ft_dstr_dtor(dstr, (void *)(tok->val = NULL));
	return (0);
}
