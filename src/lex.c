/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 12:08:43 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

extern int8_t	msh_lex_word(t_tok *tok, char peek, t_src *src);
extern int8_t	msh_lex_syntax(t_tok *tok, char peek, t_src *src);

extern t_bool	msh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (0);
	*it = msh_lex_word;
	*(it + 1) = msh_lex_syntax;
	return (1);
}
