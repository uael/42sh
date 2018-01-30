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

#define UEE "parse error: Unexpected EOF while looking for matching `}'"
#define UEH "parse error: Expected letter _ or '}' got `%c'"

static inline int	varspecial(t_tok *tok, char **it, char brace)
{
	char *var;

	if (ft_strchr("@*#?-$!", *(var = brace == '{' ? *it + 1 : *it)))
	{
		if (brace == '{' && (*(var + 1) != '}' || !ft_isspace(*(var + 2))))
			return (0);
		else if (!ft_isspace(*(var + 1)))
			return (0);
		var += brace == '{' ? 2 : 1;
	}
	else if (ft_isdigit(*var))
	{
		++var;
		while (*var && ft_isdigit(*var))
			++var;
		if (brace == '{' ? (*var != '}' || !ft_isspace(*(var + 1))) :
			!ft_isspace(*var))
			return (0);
		var += brace == '{' ? 1 : 0;
	}
	else
		return (0);
	while (*it != var)
		ft_sdscpush((t_sds *)tok, *(*it)++);
	return (1);
}

inline int			sh_lexvar(int fd, t_tok *tok, char **it, char **ln)
{
	char	brace;
	int		st;

	ft_sdscpush((t_sds *)tok, *(*it)++);
	if ((brace = **it) == '(' || ft_strchr(sh_varifs(), brace) ||
		ft_isspace(brace) || varspecial(tok, it, brace))
		return (YEP);
	if (!ft_isalpha(brace) && brace != '_' && brace != '{')
		return (sh_synerr(*ln, *it, "Expected alpha _ or '{' got `%c'", **it));
	while (ft_sdscpush((t_sds *)tok, *(*it)++))
		if (brace == '{' && !**it &&
			(fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || fd != 0 ? sh_synerr(*ln, *it, UEE) : OUF);
		else if (!**it)
			break ;
		else if (!ft_isalnum(**it) && **it != '_')
		{
			if (brace == '{' && **it != '}')
				return (sh_synerr(*ln, *it, UEH, **it));
			if (brace == '{')
				ft_sdscpush((t_sds *)tok, *(*it)++);
			break ;
		}
	return (YEP);
}
