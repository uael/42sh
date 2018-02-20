/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param/env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expparamenv(t_sds *word, char **words, t_vec *av, t_param *param)
{
	if (ft_isalpha(**words) || **words == '_')
	{
		*ft_sdspush(&param->env) = **words;
		while (ft_isalnum(*++*words) || **words == '_')
			*ft_sdspush(&param->env) = **words;
	}
	else if (ft_isdigit(**words))
	{
		param->special = 1;
		*ft_sdspush(&param->env) = **words;
		if (!param->brace)
			return (sh_expparamsubst(word, words, av, param));
		while (ft_isdigit(*++*words) || **words == '_')
			*ft_sdspush(&param->env) = **words;
	}
	else if (ft_strchr("*@$?!", **words))
	{
		param->special = 1;
		*ft_sdspush(&param->env) = *(*words)++;
	}
	else if (param->brace)
		return (NOP);
	return (YEP);
}
