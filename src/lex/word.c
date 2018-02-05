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
#include "ush/shell.h"

#define ISQUOTE(IT) (*(IT) == '\'' || *(IT) == '"'|| *(IT) == '`')
#define UEC "parse error: Unexpected EOF while looking for matching `%c'"
#define DQUOT(IT) ft_strchr("\\\n\"$", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

static inline int	quote(int fd, t_tok2 *tok, char **it, char **ln)
{
	char	q;
	int		st;
	int		bs;

	bs = 0;
	st = 0;
	ft_sdscpush((t_sds *)tok, q = *(*it)++);
	while (!st)
		if (!bs && q == '"' && (st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || !g_sh->tty ? sh_synerr(*ln, *it, UEC, q) : OUF);
		else if (bs)
			(void)(ft_sdscpush((t_sds *)tok, *(*it)++) && (bs = 0));
		else if (**it == q && ft_sdscpush((t_sds *)tok, *(*it)++))
			break ;
		else if (!(bs = **it == '\\') && q == '"' && **it == '`')
			st = quote(fd, tok, it, ln);
		else if (q == '"' && **it == '$' && *(*it + 1) &&
			!ft_isspace(*(*it + 1)) && !ft_strchr(sh_varifs(), *(*it + 1)))
			st = sh_lexvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	return (st);
}

inline int			sh_lexword(int fd, t_tok2 *tok, char **it, char **ln)
{
	int		st;
	int		bs;

	st = 0;
	bs = 0;
	while (**it && !st)
		if (!bs && (ft_isspace(**it) || ft_strchr("><&|!;()", **it) ||
			(st = sh_lexbslash(fd, it, ln))))
			break ;
		else if (bs)
			(void)(ft_sdscpush((t_sds *)tok, *(*it)++) && (bs = 0));
		else if (!(bs = **it == '\\') && ISQUOTE(*it))
			st = quote(fd, tok, it, ln);
		else if (**it == '$' && *(*it + 1) && !ft_isspace(*(*it + 1)) &&
			!ft_strchr(sh_varifs(), *(*it + 1)))
			st = sh_lexvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)tok, *(*it)++);
	if (st || !tok->len)
		return (st ? st : NOP);
	tok->id = TOK_WORD;
	return (st);
}
