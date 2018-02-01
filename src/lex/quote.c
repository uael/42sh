/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/spec.c                                         :+:      :+:    :+:   */
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
#define DQUOT(IT) ft_strchr("\\\n\"$", *(IT))
#define QUOTE(IT) (*(IT) == '\'' && (*((IT) + 1) == '\''))

static inline int	inhib(char quote, t_tok *tok, char **it)
{
	if (quote == '"')
		ft_sdscpush((t_sds *)tok, DQUOT(*it) ? *(*it)++ : (char)'\\');
	else
		ft_sdscpush((t_sds *)tok, QUOTE(*it) ? *(*it)++ : (char)'\\');
	return (0);
}

static inline int	pushvar(int fd, t_tok **t, char **it, char **ln)
{
	int		st;
	t_tok	*prev;
	t_tok	*var;

	prev = *t;
	if (prev->id != TOK_VAR)
		prev->id = TOK_WORD;
	var = (*t)->len ? ft_deqpush(g_lextoks) : prev;
	if (!(var->len = 0) && (*t)->len)
		var->spec |= TSPEC_CONTINUOUS;
	var->spec |= TSPEC_DQUOTE;
	if (!(st = sh_lexvar(fd, var, it, ln)))
	{
		var->pos = prev->pos;
		if (!ft_isspace(**it) && !ft_strchr("><&|!;(){}", **it) &&
			!(st = sh_lexbslash(fd, it, ln)) && **it != '"')
		{
			ft_sdsgrow((t_sds *)(*t = ft_deqpush(g_lextoks)), 1);
			(*t)->len = 0;
			(*t)->spec = 0;
			(*t)->spec |= TSPEC_CONTINUOUS;
			(*t)->pos = prev->pos;
		}
	}
	return (st);
}

inline int			sh_lexquote(int fd, t_tok **tok, char **it, char **ln)
{
	char	q;
	int		st;
	int		bs;

	bs = 0;
	(*tok)->spec |= ((q = *(*it)++) == '"' ? TSPEC_DQUOTE : TSPEC_SQUOTE);
	st = 0;
	while (!st)
		if (!bs && q == '"' && (st = sh_lexbslash(fd, it, ln)))
			return (st);
		else if (!**it && (fd < 0 || (st = rl_catline(fd, 0, ln, it))))
			return (st < 0 || !g_sh->tty ? sh_synerr(*ln, *it, UEC, q) : OUF);
		else if (bs)
			bs = inhib(q, *tok, it);
		else if (**it == q && ++*it)
			break ;
		else if ((bs = **it == '\\'))
			++*it;
		else if (q == '"' && **it == '$' && *(*it + 1) &&
			!ft_isspace(*(*it + 1)) && !ft_strchr(sh_varifs(), *(*it + 1)))
			st = pushvar(fd, tok, it, ln);
		else
			ft_sdscpush((t_sds *)*tok, *(*it)++);
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
