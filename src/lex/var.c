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

/*
** TODO(uael): use your brain to find a proper and working algo, this one is
** shity and make me sick
*/

#define UNPXTD "Unexpected EOF while looking for matching `}'"
#define EXPTD "Expected letter or '}' got `%c'"

inline int			sh_lexvar(int fd, t_tok *tok, char **it, char **ln)
{
	char	brace;
	t_sds	var;
	char	*val;
	int		st;

	if (**it != '$')
		return (sh_synerr(*ln, *it, "Expected token '$'"));
	ft_sdsctor(&var);
	if (ft_isalpha(brace = *++*it) || brace == '_')
		ft_sdscpush(&var, brace);
	while (++*it)
	{
		if (!**it && (st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
			return (st < 0 ? WUT : sh_synerr(*ln, *it, UNPXTD));
		if (!ft_isalnum(**it) && **it != '_')
		{
			if (brace == '{' && **it != '}')
				return (sh_synerr(*ln, *it, EXPTD, **it));
			else if (brace == '{')
				++*it;
			break ;
		}
		ft_sdscpush(&var, **it);
	}
	ft_sdsapd((t_sds *)tok, var.len && (val = sh_varget(var.buf)) ? val : "");
	ft_sdsdtor(&var);
	return (YEP);
}
