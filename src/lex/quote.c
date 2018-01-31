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
#include "ush/shell.h"

#define UEC "parse error: Unexpected EOF while looking for matching `%c'"
#define DQUOT(IT) ft_strchr("\\\n\"", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

static inline int	inhib(char quote, t_tok *tok, char **it)
{
	if (quote == '"')
		ft_sdscpush((t_sds *)tok, DQUOT(*it) ? *(*it)++ : (char)'\\');
	else
		ft_sdscpush((t_sds *)tok, QUOTE(*it) ? *(*it)++ : (char)'\\');
	return (0);
}

inline int			sh_lexquote(int fd, t_tok *tok, char **it, char **ln)
{
	char	quote;
	int		st;
	int		bs;

	bs = 0;
	quote = *(*it)++;
	st = 0;
	while (!st)
		if (!bs && quote == '"' && (st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || !g_sh->interact ?
				sh_synerr(*ln, *it, UEC, quote) : OUF);
		else if (bs)
			bs = inhib(quote, tok, it);
		else if (**it == quote && ++*it)
			break ;
		else if ((bs = **it == '\\'))
			++*it;
		else if (**it == '$' && (*it == *ln || *(*it - 1) != '\\'))
			st = sh_lexvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	return (st);
}

inline int			sh_lexbslash(int fd, char **it, char **ln)
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
