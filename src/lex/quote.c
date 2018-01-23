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

#define UNXPTD "Unexpected EOF while looking for matching `%c'"
#define DQUOT(IT) ft_strchr("\\\n\"$", **(IT))
#define QUOTE(IT) (**(IT) == '\'')

inline int	sh_lexquote(int fd, t_tok *tok, char **it, char **ln)
{
	char	quote;
	int		st;
	int		bs;

	bs = 0;
	if ((quote = *(*it)++) != '\'' && quote != '"')
		return (sh_synerr(*ln, *it, "Expected token ''' or '\"'"));
	while (1)
		if (!**it && (st = fd < 0 ? NOP : rl_catline(fd, 0, ln, it)))
			return (st < 0 ? WUT : sh_synerr(*ln, *it, UNXPTD, quote));
		else if (bs)
		{
			bs = 0;
			if (quote == '"')
				ft_sdscpush((t_sds *)tok, DQUOT(it) ? *(*it)++ : (char)'\\');
			else
				ft_sdscpush((t_sds *)tok, QUOTE(it) ? *(*it)++ : (char)'\\');
		}
		else if (**it == quote && ++*it)
			break ;
		else if ((bs = **it == '\\'))
			++*it;
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	return (YEP);
}
