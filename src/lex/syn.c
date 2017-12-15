/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/syn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

inline int				sh_lex_syn(t_lexer *lex, t_tok *tok, char peek)
{
	ssize_t sz;

	while (peek == ' ' || peek == '\t')
	{
		ft_lexer_getc(lex, NULL, &peek);
	}
	if (ft_strchr("=!()-;[]{|}\n", peek))
	{
		tok->val = NULL;
		tok->id = (uint8_t)peek;
		if ((sz = ft_lexer_next(lex, NULL, 1)) <= 0)
			return (sz < 0 ? WUT : NOP);
		return (YEP);
	}
	return (NOP);
}
