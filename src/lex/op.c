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

static inline int	lex_match(t_sh_tok *tok, char **ln, uint8_t len, uint8_t id)
{
	tok->id = id;
	tok->val = *ln;
	*ln += (tok->len += len);
	return (YEP);
}

inline int			sh_lex_op(t_sh_tok *tok, char **ln)
{
	char *b;

	tok->len = (size_t)ft_isdigit(**ln);
	if ((b = *ln + tok->len)[0] == '>' && b[1] == '>' && b[2] == '-')
		return (lex_match(tok, ln, 3, SH_TOK_HEREDOCT));
	if (b[0] == '>' && b[1] == '>')
		return (lex_match(tok, ln, 2, SH_TOK_RAOUT));
	if (b[0] == '&' && b[1] == '>')
		return (lex_match(tok, ln, 2, SH_TOK_AMPR));
	if (b[0] == '>' && b[1] == '&')
		return (lex_match(tok, ln, 2, SH_TOK_RAMP));
	if (b[0] == '>' && b[1] == '|')
		return (lex_match(tok, ln, 2, SH_TOK_RPOUT));
	if (b[0] == '|' && b[1] == '|')
		return (lex_match(tok, ln, 2, SH_TOK_LOR));
	if (b[0] == '<' && b[1] == '>')
		return (lex_match(tok, ln, 2, SH_TOK_CMP));
	if (b[0] == '<' && b[1] == '<')
		return (lex_match(tok, ln, 2, SH_TOK_HEREDOC));
	if (b[0] == '<' && b[1] == '&')
		return (lex_match(tok, ln, 2, SH_TOK_LAMP));
	if (b[0] == '&' && b[1] == '&')
		return (lex_match(tok, ln, 2, SH_TOK_LAND));
	return (b[0] == '>' || b[0] == '<' ?
		lex_match(tok, ln, 1, (uint8_t)b[0]) : NOP);
}
