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

#include "msh/lex.h"
#include "msh/var.h"

inline int			sh_lexvar(int fd, t_tok *tok, char **it, char **ln)
{
	char	brace;
	t_sds	var;
	char	*val;

	if (**it != '$')
		return (ENO_THROW(WUT, EINVAL));
	ft_sdsctor(&var);
	if (ft_isalpha(brace = *++*it) || brace == '_')
		ft_sdscpush(&var, brace);
	while (++*it)
	{
		if (!**it && (fd < 0 || !(*it = rl_catline(fd, "> ", 0, ln))))
			return (ENO_THROW(WUT, EINVAL));
		if (!ft_isalnum(**it) && **it != '_')
		{
			if (brace == '{' && **it != '}')
				return (WUT);
			else if (brace == '{')
				++*it;
			break ;
		}
		ft_sdscpush(&var, **it);
	}
	if (var.len && (val = sh_varget(var.buf)))
		ft_sdsapd((t_sds *)tok, val);
	ft_sdsdtor(&var);
	return (YEP);
}

