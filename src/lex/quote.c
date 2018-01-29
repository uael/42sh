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
	char	q;
	int		st;
	int		bs;

	bs = 0;
	if ((q = *(*it)++) != '\'' && q != '"')
		return (sh_synerr(*ln, *it, "Expected token ''' or '\"'"));
	while (1)
		if (!**it && (fd < 0  || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || fd != 0 ? sh_synerr(*ln, *it, UNXPTD, q) : OUF);
		else if (bs)
		{
			bs = 0;
			if (q == '"')
				ft_sdscpush((t_sds *)tok, DQUOT(it) ? *(*it)++ : (char)'\\');
			else
				ft_sdscpush((t_sds *)tok, QUOTE(it) ? *(*it)++ : (char)'\\');
		}
		else if (**it == q && ++*it)
			break ;
		else if ((bs = **it == '\\'))
			++*it;
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	return (YEP);
}

inline int	sh_lexbquote(int fd, char **it, char **ln)
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
