/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	sh_expparamdone(t_param *param, int st)
{
	if (param->freev && param->val)
		free(param->val);
	ft_sdsdtor(&param->env);
	return (st);
}

/*
** TODO: allow null word param to check substitution error on lexing
*/

int	sh_expparam(t_sds *word, char **words, t_vec *av, t_bool quoted)
{
	int		st;
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	param.start = *words;
	param.quoted = quoted;
	if ((param.brace = (t_bool)(**words == '{')))
		++*words;
	if (**words == '#')
	{
		param.hash = 1;
		if (!param.brace)
			return (sh_expparamsubst(word, words, av, &param));
		++*words;
	}
	if ((st = sh_expparamenv(word, words, av, &param)))
		return (st == NOP ? NOP : YEP);
	if (!param.brace)
		--*words;
	return (sh_expparamsubst(word, words, av, &param));
}
