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
#include "ush/shell.h"

#define UEE "parse error: Unexpected EOF while looking for matching `%c'"
#define UEC "parse error: Expected closing '%c' got `%c'"
#define UEB "parse error: Unexpected closing bracket `%c'"

static char	bracket(char c)
{
	if (c == '{')
		return ('}');
	if (c == '[')
		return (']');
	if (c == '(')
		return (')');
	return (0);
}

static int	brackets(int fd, t_tok *tok, char **it, char **ln)
{
	char	stack[1000];
	int		st;
	int		i;
	char	*br;

	i = 0;
	stack[i++] = bracket(**it);
	br = NULL;
	while (++tok->len && ++*it)
	{
		if (!i && (!**it || br))
			break ;
		if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it)) || !**it))
		{
			return (LEX_SHOWE(st, fd) ?
				sh_synerr(*ln, *it, UEE, stack[i - 1]) : OUF);
		}
		if (ft_strchr("[{(", **it))
			stack[i++] = bracket(**it);
		else if ((br = ft_strchr("]})", **it)) && !i)
			return (sh_synerr(*ln, *it, UEB, **it));
		else if (br && **it != stack[--i])
			return (sh_synerr(*ln, *it, UEC, stack[i], **it));
	}
	return (YEP);
}

inline int	sh_lexdollar(int fd, t_tok *tok, char **it, char **ln)
{
	if (**it != '$')
		return (NOP);
	(void)(++tok->len && ++*it);
	if (ft_strchr("[{(", **it))
		return (brackets(fd, tok, it, ln));
	return (YEP);
}
