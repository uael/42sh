/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

inline int				sh_lexword(int fd, t_tok *tok, char **it, char **ln)
{
	char	*beg;
	int		st;

	beg = *it;
	st = 0;
	while (**it && !st)
		if (ft_isspace(**it) || ft_strchr("><&|!;(){}", **it))
			break ;
		else if ((**it == '\'' || **it == '"'))
			st = sh_lexquote(fd, tok, it, ln);
		else if (**it == '\\' && ((*(*it + 1) == '\n' && !*(*it + 2)) ||
			(*(*it + 1) == '\r' && *(*it + 2) == '\n' && !*(*it + 3))))
			st = fd < 0 ? NOP : rl_catline(fd, -2, ln, it);
		else if (**it == '$')
			st = sh_lexvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	if (st || (!tok->len && beg == *it))
		return (st ? st : NOP);
	tok->id = TOK_WORD;
	sh_wordglob((t_sds *)tok);
	return (YEP);
}
