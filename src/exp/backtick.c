/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/backtick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expbacktick(t_sds *word, char **words, t_vec *av)
{
	t_sds	comm;
	t_bool	quote;

	quote = 0;
	ft_sdsctor(&comm);
	--*words;
	while (*++*words)
		if (**words == '`')
			return (sh_expcommexec(word, &comm, av));
		else if (**words == '\\')
			sh_expbackslash(&comm, words, quote);
		else if (**words == '\'')
			quote ^= 1;
		else
			*ft_sdspush(&comm) = **words;
	return (NOP);
}
