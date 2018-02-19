/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/exp.h"

int	onparentheses(t_sds *word, char **words, t_vec *av, char quote)
{
	int		i;
	int		depth;

	if (*(*words + 2) == '(')
	{
		i = 3;
		depth = 0;
		while ((*words)[i] && !(!depth && (*words)[i] == ')'))
		{
			if ((*words)[i] == '(')
				++depth;
			else if ((*words)[i] == ')')
				--depth;
			++i;
		}
		if ((*words)[i] == ')' && (*words)[i + 1] == ')')
		{
			*words += 3;
			return (sh_exparith(word, words, 0));
		}
	}
	*words += 2;
	return (sh_expcomm(word, words, quote ? NULL : av));
}

int	sh_expdollars(t_sds *word, char **words, t_vec *av, char quote)
{
	char	c;


	c = *(*words + 1);
	if (!c || c == '\'' || c == '"')
	{
		*ft_sdspush(word) = '$';
		return (YEP);
	}
	else if (c == '(')
		return (onparentheses(word, words, av, quote));
	else if (c == '[')
	{
		*words += 2;
		return (sh_exparith(word, words, 1));
	}
	++*words;
	return (sh_expparam(word, words, av, quote));
}
