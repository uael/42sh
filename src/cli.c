/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "msh.h"

int	main(void)
{
	t_lexer lexer;
	t_tok	tok;

	if (!ft_lexer_init_str(&lexer, "for in do done\n") || !msh_lex(&lexer))
		return (EXIT_FAILURE);
	if (ft_lexer_scan(&lexer, 7) > 0)
		while (ft_vec_shift(&lexer.toks, &tok))
			if (tok.is_id)
			{
				if (tok.id.id == MSH_TOK_FOR)
					ft_putl(1, "for");
				else if (tok.id.id == MSH_TOK_DO)
					ft_putl(1, "do");
				else if (tok.id.id == MSH_TOK_IN)
					ft_putl(1, "in");
				else if (tok.id.id == MSH_TOK_DONE)
					ft_putl(1, "done");
			}
	return (EXIT_SUCCESS);
}
