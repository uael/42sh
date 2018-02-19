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

#define UEE "parse error: Unexpected EOF while looking for matching `}'"
#define UEH "parse error: Expected letter _ or '}' got `%c'"
#define UEC "parse error: Expected closing '}' got `%c'"

static inline int	varspecial(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;
	char	*var;
	t_bool	brace;

	var = *it;
	brace = (t_bool)(*var == '{' && ++var);
	if (!*var)
		return (NOP);
	if (ft_strchr("#?$!", *var))
		++var;
	else if (ft_isdigit(*var) && ++var)
		while (*var && ft_isdigit(*var))
			++var;
	else
		return (NOP);
	tok->len += var - *it;
	*it += var - *it;
	st = 0;
	if (brace && !*var && (fd < 0 || (st = rl_catline(fd, 0, ln, it)) || !**it))
		return (LEX_SHOWE(st, fd) ? sh_synerr(*ln, *it, UEE) : OUF);
	return (brace && **it != '}' ? sh_synerr(*ln, *it, UEC, **it) :
		((brace && ++*it) & 0));
}

static inline int	varuser(int fd, t_tok *tok, char **it, char **ln)
{
	char	brace;
	int		st;

	st = 0;
	brace = **it;
	if (!ft_isalpha(brace) && brace != '_' && brace != '{')
		return (sh_synerr(*ln, *it, "Expected alpha _ or '{' got `%c'", **it));
	while ((++tok->len && ++*it))
		if (brace == '{' && !**it &&
			(fd < 0 || (st = rl_catline(fd, 0, ln, it)) || !**it))
			return (LEX_SHOWE(st, fd) ? sh_synerr(*ln, *it, UEE) : OUF);
		else if (!**it)
			break ;
		else if (!ft_isalnum(**it) && **it != '_')
		{
			if (brace == '{' && **it != '}')
				return (sh_synerr(*ln, *it, UEH, **it));
			if (brace == '{')
				(void)(++tok->len && ++*it);
			break ;
		}
	return (YEP);
}

/*
** TODO: just check for matching } or )
*/

inline int			sh_lexdollar(int fd, t_tok *tok, char **it, char **ln)
{
	int		st;

	if (**it != '$')
		return (NOP);
	(void)(++tok->len && ++*it);
	if ((st = varspecial(fd, tok, it, ln)) > NOP)
		return (st);
	if (st && (st = varuser(fd, tok, it, ln)))
		return (st);
	return (YEP);
}