/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 07:41:18 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "msh.h"

extern t_ret	msh_lex_word(t_tok *tok, char peek, t_src *src);
extern t_ret	msh_lex_syntax(t_tok *tok, char peek, t_src *src);

void			msh_dtor(t_lexer *lexer)
{
	ft_lexer_dtor(lexer);
}

t_ret			msh_lex(t_lexer *self)
{
	t_lrule *it;

	if (!(it = ft_vec_pushn(&self->rules, 2)))
		return (RET_ERR);
	*it = msh_lex_word;
	*(it + 1) = msh_lex_syntax;
	return (RET_OK);
}

int				main(void)
{
	t_lexer lexer;
	t_tok	tok;

	if (ft_lexer_init_stream(&lexer, cin) || msh_lex(&lexer) < 0)
		return (EXIT_FAILURE);
	while (ft_lexer_next(&lexer, 1, &tok))
	{
		printf("TOKEN %d\n", tok.id);
		if (tok.id == '\n')
			break ;
	}
	ft_lexer_dtor(&lexer);
	return (EXIT_SUCCESS);
}
