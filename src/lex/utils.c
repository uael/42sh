/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline t_bool	sh_isident(char const *word, size_t n)
{
	if (!n || (!ft_isalpha(*word) && *word != '_'))
		return (0);
	++word;
	while (--n)
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (0);
		++word;
	}
	return (1);
}

inline t_bool	sh_iseol(char const *it)
{
	return ((t_bool)(sh_isreol(it) || sh_isweol(it)));
}

inline t_bool	sh_isreol(char const *it)
{
	return ((t_bool)(*it == '\n'));
}

inline t_bool	sh_isweol(char const *it)
{
	return ((t_bool)(*it == '\r' && *(it + 1) == '\n'));
}
