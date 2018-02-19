/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param/pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expparampattern(t_sds *word, char **words, t_vec *av, t_param *param)
{
	int		depth;
	uint8_t	pquoted;

	if (**words == '}')
		return (sh_expparamsubst(word, words, av, param));
	else if (**words == '#')
	{
		param->act = ACT_RP_SHORT_LEFT;
		if (*(*words + 1) == '#')
		{
			++*words;
			param->act = ACT_RP_LONG_LEFT;
		}
	}
	else if (**words == '%')
	{
		param->act = ACT_RP_SHORT_RIGHT;
		if (*(*words + 1) == '#')
		{
			++*words;
			param->act = ACT_RP_LONG_RIGHT;
		}
	}
	else if (**words == ':')
	{
		if (!ft_strchr("-=?+", *(*words + 1)))
			return (sh_expparamdone(param, NOP, NULL, 0));
		param->colon = 1;
		param->act = (enum e_act)*++*words;
	}
	else if (ft_strchr("-=?+", **words))
		param->act = (enum e_act)*++*words;
	else
		return (sh_expparamdone(param, NOP, NULL, 0));
	depth = 0;
	pquoted = 0;
	while (*++*words)
	{
		if (**words == '{')
			pquoted ? 0 : ++depth;
		else if (**words == '}')
		{
			if (!pquoted)
			{
				if (!depth)
					return (sh_expparamsubst(word, words, av, param));
				--depth;
			}
		}
		else if (**words == '\\')
		{
			if (!pquoted)
			{
				if (!*++*words)
					return (sh_expparamdone(param, NOP, NULL, 0));
				*ft_sdspush(&param->pattern) = '\\';
			}
		}
		else if (**words == '\'')
		{
			if (!pquoted)
				pquoted = 1;
			else if (pquoted == 1)
				pquoted = 0;
		}
		else if (**words == '"')
		{
			if (!pquoted)
				pquoted = 2;
			else if (pquoted == 2)
				pquoted = 0;
		}
		*ft_sdspush(&param->pattern) = **words;
	}
	return (YEP);
}
