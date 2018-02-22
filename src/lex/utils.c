/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/reduce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/22 12:51:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline t_bool	sh_isname(char *word)
{
	if (!ft_isalpha(*word) && *word != '_')
		return (0);
	++word;
	while (*word && *word != '=')
	{
		if (!ft_isalnum(*word) && *word != '_')
			return (0);
		++word;
	}
	return (1);
}

inline int		sh_lexbslash(int fd, char **it, char **ln)
{
	int st;

	if (**it == '\\' && ((ISREOL(*it + 1) && !*(*it + 2)) ||
		((ISWEOL(*it + 1) && !*(*it + 3)))))
	{
		*it += ISREOL(*it + 1) ? 2 : 3;
		if (fd >= 0 && (st = rl_catline(fd, -2, ln, it)))
			return (st);
	}
	return (YEP);
}
