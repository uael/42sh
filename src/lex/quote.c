/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline int	sh_lexquote(int fd, t_tok *tok, char **it, char **ln)
{
	char quote;

	if ((quote = *(*it)++) != '\'' && quote != '"')
		return (sh_synerr(*ln, *it, "Expected token ''' or '\"'"));
	while (1)
		if (!**it && (fd < 0 || !(*it = rl_catline(fd, "> ", 0, ln))))
			return (*it == (char *)-1 ? WUT : sh_synerr(*ln, *it, "Unexpected "
				"EOF while looking for matching `%c'", quote));
		else if (quote == '"' && *(*it - 1) == '\\')
			ft_sdscpush((t_sds *)tok, ft_strchr("\\\n\"$", **it)
				? *(*it)++ : (char)'\\');
		else if (quote == '\'' && *(*it - 1) == '\\')
			ft_sdscpush((t_sds *)tok, **it == '\'' ? *(*it)++ : (char)'\\');
		else if (**it == quote && ++*it)
			break ;
		else if (**it == '\\')
			++*it;
		else if (**it == '$')
		{
			if (sh_lexvar(fd, tok, it, ln))
				return (WUT);
		}
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	return (YEP);
}
