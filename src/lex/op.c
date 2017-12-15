/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static inline int		lex_op_match(t_lexer *lex, t_tok *tok, size_t n, int *m)
{
	ssize_t sz;

	tok->id = (uint8_t)m[0];
	if (m[1])
		ft_tokv_init_i32(tok->val, m[1] - '0');
	else
		tok->val = NULL;
	if ((sz = ft_lexer_next(lex, NULL, m[1] ? n + 1 : n)) <= 0)
		return (sz < 0 ? WUT : NOP);
	return (YEP);
}

static inline int		lex_op_3(t_lexer *lex, t_tok *tok, char *b)
{
	char d;

	d = ft_isdigit(*b) ? *b++ : (char)'\0';
	if (b[0] == '<' && b[1] == '<' && b[2] == '-')
		return (lex_op_match(lex, tok, 3, (int[2]){SH_TOK_HEREDOCT, d}));
	return (NOP);
}

static inline int		lex_op_2(t_lexer *lex, t_tok *tok, char *b)
{
	char d;

	d = ft_isdigit(*b) ? *b++ : (char)'\0';
	if (b[0] == '>' && b[1] == '>')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_RAOUT, d}));
	if (b[0] == '&' && b[1] == '>')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_AMPR, d}));
	if (b[0] == '>' && b[1] == '&')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_RAMP, d}));
	if (b[0] == '>' && b[1] == '|')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_RPOUT, d}));
	if (b[0] == '|' && b[1] == '|')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_LOR, d}));
	if (b[0] == '<' && b[1] == '>')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_CMP, d}));
	if (b[0] == '<' && b[1] == '<')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_HEREDOC, d}));
	if (b[0] == '<' && b[1] == '&')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_LAMP, d}));
	if (b[0] == '&' && b[1] == '&')
		return (lex_op_match(lex, tok, 2, (int[2]){SH_TOK_LAND, d}));
	return (NOP);
}

static inline int		lex_op_1(t_lexer *lex, t_tok *tok, char *b)
{
	char d;

	d = ft_isdigit(*b) ? *b++ : (char)'\0';
	if (b[0] == '>' || b[0] == '<')
		return (lex_op_match(lex, tok, 1, (int[2]){b[0], d}));
	return (NOP);
}

inline int				sh_lex_op(t_lexer *lex, t_tok *tok, char peek)
{
	char	b[4];
	size_t	n;
	int		st;

	n = 0;
	b[n] = peek;
	while (++n < 4 && b[n - 1] && b[n - 1] != '\n')
		if ((st = ft_lexer_peek(lex, b + n, n)) < 0)
			return (st);
		else if (st)
			break ;
	if (n >= 3 && (st = lex_op_3(lex, tok, b)) <= 0)
		return (st);
	if (n >= 2 && (st = lex_op_2(lex, tok, b)) <= 0)
		return (st);
	if (n >= 1 && (st = lex_op_1(lex, tok, b)) <= 0)
		return (st);
	return (NOP);
}
