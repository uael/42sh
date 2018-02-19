/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/backslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expbackslash(t_sds *word, char **words, t_bool quote)
{
	char c;

	c = *(*words + 1);
	if (!c)
		return (NOP);
	if (c != '\n')
	{
		if (quote && !ft_strchr("$`\"\\", c))
			*ft_sdspush(word) = '\\';
		*ft_sdspush(word) = c;
	}
	++*words;
	return (YEP);
}
