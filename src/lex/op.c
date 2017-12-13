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

#define M(p, c) (s[p] == (c))
#define W SH_TOK_WORD
#define TOK(T) SH_TOK_ ## T
#define MATCH(tok, src, n, id) ft_lexer_match(tok, src, n, id)

inline int				sh_lex_op(t_tok *tok, char peek, t_src *src)
{
	char	b[3];
	char	*c;
	size_t	n;

	n = 0;
	b[n] = peek;
	while (++n < 3 && b[n - 1] && b[n - 1] != '\n')
		if (ft_src_peek(src, b + n, n))
			break ;
	if (n == 3 && b[0] == '>' && b[1] == '>' && b[2] == '-')
		return (MATCH(tok, src, 3, SH_TOK_RARROW));
	if (n >= 2 && b[1] == '>' && (b[0] == '>' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RAOUT) : TOK(AMPR)));
	if (n >= 2 && b[0] == '>' && b[1] == '&')
		return (MATCH(tok, src, 2, SH_TOK_RAMP));
	if (n >= 2 && b[1] == '|' && (b[0] == '>' || b[0] == '|'))
		return (MATCH(tok, src, 2, b[0] == '>' ? TOK(RPIPE) : TOK(LOR)));
	if (n >= 2 && b[0] == '<' && (b[1] == '>' || b[1] == '<'))
		return (MATCH(tok, src, 2, b[1] == '>' ? TOK(CMP) : TOK(HEREDOC)));
	if (n >= 2 && b[1] == '&' && (b[0] == '<' || b[0] == '&'))
		return (MATCH(tok, src, 2, b[0] == '<' ? TOK(LAMP) : TOK(LAND)));
	return ((n >= 1 && (c = ft_strchr("=\t\n !&()-;<=>[]{|}", peek))) ?
			MATCH(tok, src, 1, (uint8_t)*c) : NOP);
}