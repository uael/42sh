/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"
#include "ush/var.h"

#define UNPXTD "Unexpected EOF while looking for matching `}'"
#define EXPTD "Expected letter _ or '}' got `%c'"

inline int			sh_lexvar(int fd, t_tok *tok, char **it, char **ln)
{
	char	brace;
	int		st;

	ft_sdscpush((t_sds *)tok, *(*it)++);
	if ((brace = **it) == '(' || ft_strchr(sh_varifs(), brace))
		return (YEP);
	if (!ft_isalpha(brace) && brace != '_' && brace != '{')
		return (sh_synerr(*ln, *it, "Expected alpha _ or '{' got `%c'", **it));
	while (ft_sdscpush((t_sds *)tok, *(*it)++))
	{
		if (brace == '{' && !**it &&
			(st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
			return (st < 0 ? WUT : sh_synerr(*ln, *it, UNPXTD));
		if (!**it)
			break ;
		if (!ft_isalnum(**it) && **it != '_')
		{
			if (brace == '{' && **it != '}')
				return (sh_synerr(*ln, *it, EXPTD, **it));
			if (brace == '{')
				ft_sdscpush((t_sds *)tok, *(*it)++);
			break ;
		}
	}
	return (YEP);
}
