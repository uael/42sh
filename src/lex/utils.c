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

inline int		sh_lexbslash(t_src *s)
{
	int st;

	if (**s->it == '\\' && ((ISREOL(*s->it + 1) && !*(*s->it + 2)) ||
		((ISWEOL(*s->it + 1) && !*(*s->it + 3)))))
	{
		*s->it += ISREOL(*s->it + 1) ? 2 : 3;
		if (s->fd >= 0 && (st = rl_catline(s->fd, -2, s->ln, s->it)))
			return (st);
	}
	return (YEP);
}
