/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 13:05:55 by null             ###   ########.fr       */
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
	while (ft_lexer_next(&lexer, &tok))
		printf("TOKEN %d\n", tok.id);
	return (EXIT_SUCCESS);
}
