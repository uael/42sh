/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/comm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expdquote(t_sds *word, char **words, t_vec *av)
{
	--*words;
	while (*++*words)
		if (**words == '"')
			return (YEP);
		else if (**words == '$')
			sh_expdollars(word, words, av, 1);
		else if (**words == '`')
		{
			++*words;
			sh_expbacktick(word, words, av);
		}
		else if (**words == '\\')
			sh_expbackslash(word, words, 1);
		else
			*ft_sdspush(word) = **words;
	return (NOP);
}

int	sh_expsquote(t_sds *word, char **words)
{
	return (42);
}
