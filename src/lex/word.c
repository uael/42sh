/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

#define M(p, c) (s[p] == (c))
#define W SH_TOK_WORD

static inline int		word_pp(t_lexer *lex, char *peek, char *t)
{
	int		st;

	if ((*peek == '\'' || *peek == '\"') && (!*t || *t == *peek))
	{
		*t = (char)(*t ? '\0' : *peek);
		if ((st = ft_lexer_getc(lex, NULL, peek)) != 0)
			return (st);
		return (word_pp(lex, peek, t));
	}
	if (!*t && *peek != '\\' && ft_strchr("|&;<>()$`\\\"' \n\t", *peek))
		return (NOP);
	else if (*peek != '\\')
		return (YEP);
	if ((st = ft_lexer_peek(lex, peek, 1)))
		return (st);
	if (*t && !ft_strchr(*t == '\"' ? "$`\"\\\n" : "'", *peek))
		return (NOP);
	if (!*t && !ft_strchr("|&;<>()$`\\\"' \n\t", *peek))
		return (NOP);
	return (ft_lexer_next(lex, NULL, 1) < 0 ? WUT : YEP);
}

static inline uint8_t	word_keyword(char const *s, size_t l)
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

inline int				sh_lex_word_lol(t_lexer *lex, t_tok *tok, char peek)
{
	t_dstr	*dstr;
	int		st;
	char	t;

	t = '\0';
	dstr = &tok->val->val.ident;
	if (!dstr->buf)
		ft_dstr_ctor(dstr);
	while (peek && (st = word_pp(lex, &peek, &t)) == 0)
	{
		ft_dstr_pushc(dstr, peek);
		if ((st = ft_lexer_getc(lex, NULL, &peek)))
			return (st);
	}
	if (st < 0 || dstr->len == 0)
		return (ft_dtor(st < 0 ? st : NOP, (t_dtor)ft_dstr_dtor, dstr, NULL));
	if ((tok->id = word_keyword(dstr->buf, dstr->len)) == W)
		tok->val->kind = TOKV_IDENT;
	else
		ft_dstr_dtor(dstr, (void *)(tok->val = NULL));
	return (YEP);
}

inline int				sh_lex_quote(t_sh_tok *tok, char **ln)
{
	char	buf[LN_MAX];
	char	quote;

	quote = **ln;
	while (*++*ln)
	{
		if (**ln == quote)
			break ;
		if (!**ln)
	}
}

inline int				sh_lex_word(t_sh_tok *tok, char **ln)
{
	char	*word;
	size_t	len;
	int		st;
	char	quote;

	quote = '\0';
	while (**ln)
	{
		if ((**ln == '\'' || **ln == '\"') && (!quote || quote == **ln))
		{
			quote = (char)(quote ? '\0' : **ln);
			if (quote && (!*++*ln && !(*ln = sh_readcat(rl, "> "))))
				return (WUT); //todo syntax error
		}
		else if (!quote && **ln != '\\' && ft_strchr("|&;<>()$`\\\"' \n\t", **ln))
			break ;
		else if (**ln == '\\')
		{
			if (!*(*ln + 1))
			{
				if (!(*ln = rl_readnext(rl, "> ")))
					return (WUT); //todo syntax error
			}
			else if (quote && !ft_strchr(quote == '\"' ? "$`\"\\\n" : "'", *(*ln + 1)))
				break ;
			else if (!quote && !ft_strchr("|&;<>()$`\\\"' \n\t", *(*ln + 1)))
				break ;
			++*ln;
		}
	}
	if (st < 0 || len == 0)
		return (ft_dtor(st < 0 ? st : NOP, (t_dtor)ft_pfree, &word, NULL));
}
