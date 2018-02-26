/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/dollar.c                                       :+:      :+:    :+:   */
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

static int	brackets(t_src *s, t_tok *tok)
{
	char	stack[1000];
	int		st;
	int		i;
	char	*br;

	i = 0;
	stack[i++] = bracket(**s->it);
	br = NULL;
	while (++tok->len && ++*s->it)
		if (!i && (!**s->it || br))
			break ;
		else if (!**s->it && (s->fd < 0 ||
			(st = rl_catline(s->fd, 0, s->ln, s->it)) || !**s->it))
		{
			return (LEXE(st, s->fd) ?
				sh_synerr(*s->ln, *s->it, UEE, stack[i - 1]) : OUF);
		}
		else if (ft_strchr("[{(", **s->it))
			stack[i++] = bracket(**s->it);
		else if ((br = ft_strchr("]})", **s->it)) && !i)
			return (sh_synerr(*s->ln, *s->it, UEB, **s->it));
		else if (br && **s->it != stack[--i])
			return (sh_synerr(*s->ln, *s->it, UEC, stack[i], **s->it));
	return (YEP);
}

inline int	sh_lexdollar(t_src *s, t_tok *tok)
{
	if (**s->it != '$')
		return (NOP);
	(void)(++tok->len && ++*s->it);
	if (ft_strchr("[{(", **s->it))
		return (brackets(s, tok));
	return (YEP);
}
