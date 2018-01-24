/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/lex.h"

#define UNXPTD_C "Unexpected token `%c' while looking for matching `%c'"
#define UXPTD "Unexpected closing bracket `%c'"

static char		*g_tokidsstr[] =
{
	[TOK_END] = "<EOF>",
	[TOK_HEREDOC] = "<<",
	[TOK_HEREDOCT] = "<<-",
	[TOK_RAOUT] = ">>",
	[TOK_LAMP] = "<&",
	[TOK_RAMP] = ">&",
	[TOK_CMP] = "<>",
	[TOK_EOL] = "<newline>",
	[TOK_RPOUT] = ">|",
	[TOK_AMPR] = "&>",
	[TOK_LAND] = "&&",
	[TOK_LOR] = "||",
	[TOK_CASE] = "case",
	[TOK_DO] = "do",
	[TOK_DONE] = "done",
	[TOK_ELIF] = "elif",
	[TOK_ELSE] = "else",
	[TOK_FUNCTION] = "function",
	[TOK_FOR] = "for",
	[TOK_FI] = "fi",
	[TOK_IF] = "if",
	[TOK_IN] = "in",
	[TOK_ESAC] = "esac",
	[TOK_SELECT] = "select",
	[TOK_THEN] = "then",
	[TOK_UNTIL] = "until",
	[TOK_WHILE] = "while",
	[TOK_WORD] = "<word>",
	[TOK_NOT] = "!",
	[TOK_AMP] = "&",
	[TOK_LPAR] = "(",
	[TOK_RPAR] = ")",
	[TOK_HYPEN] = "-",
	[TOK_SEMICOLON] = ";",
	[TOK_RIN] = "<",
	[TOK_ASSIGN] = "=",
	[TOK_ROUT] = ">",
	[TOK_LBRACKET] = "[",
	[TOK_RBRACKET] = "]",
	[TOK_LCURLY] = "{",
	[TOK_PIPE] = "|",
	[TOK_RCURLY] = "}"
};

inline char			*sh_tokidstr(uint8_t id)
{
	char *ret;

	if (id > TOK_RCURLY)
		return ("<unknown>");
	return ((ret = g_tokidsstr[id]) ? ret : "<unknown>");
}

inline char			*sh_tokstr(t_tok *tok)
{
	char *ret;

	if (!tok)
		return (g_tokidsstr[TOK_END]);
	if (tok->id > TOK_RCURLY)
		return ("<unknown>");
	if (tok->len)
		return (tok->val);
	return ((ret = g_tokidsstr[tok->id]) ? ret : "<unknown>");
}

static inline int	lex(int fd, t_tok *tok, char **it, char **ln)
{
	int	st;

	tok->len = 0;
	while (1)
		if (**it && ft_strchr(sh_varifs(), **it))
			++*it;
		else if (**it == '\n' || (**it == '\r' && *(*it + 1) == '\n'))
		{
			tok->pos = (uint16_t)(*it - *ln);
			++*it;
			while (**it == '\n' || (**it == '\r' && *(*it + 1) == '\n'))
				++*it;
			tok->id = TOK_EOL;
			ft_sdscpush((t_sds *)tok, '\n');
			return (YEP);
		}
		else if (**it == '\\' && ((*(*it + 1) == '\n' && !*(*it + 2)) ||
			((*(*it + 1) == '\r' && *(*it + 2) == '\n' && !*(*it + 3)))))
		{
			*it += (*(*it + 1) == '\n') ? 2 : 3;
			if (fd >= 0 && (st = rl_catline(fd, -2, ln, it)))
				return (st);
		}
		else if (**it == '#')
			while (**it && (**it != '\n' ||
				(**it != '\r' && *(*it + 1) != '\n')))
				++*it;
		else if (!**it)
		{
			tok->pos = (uint16_t)(*it - *ln);
			tok->id = TOK_END;
			return (YEP);
		}
		else
			break ;
	tok->pos = (uint16_t)(*it - *ln);
	if (ft_isdigit(**it))
		ft_sdscpush((t_sds *)tok, *(*it)++);
	if ((st = sh_lexop(fd, tok, it, ln)) != NOP)
		return (st);
	if ((st = sh_lexword(fd, tok, it, ln)) != NOP)
		return (st);
	return (sh_synerr(*ln, *it, "Unexpected token `%c'", **it));
}

int					sh_lex(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok	*tok;
	int		st;
	char	stack[1000];
	size_t	i;

	if (!**it)
		return (NOP);
	if (!ln)
		ln = it;
	i = 0;
	while ((tok = ft_deqpush(toks)))
	{
		ft_sdsgrow((t_sds *)tok, 1);
		*tok->val = '\0';
		if (!**it)
		{
			if (!i)
			{
				tok->id = TOK_END;
				break ;
			}
			if ((st = fd < 0 ? NOP : rl_catline(fd, -1, ln, it)))
				return (st);
		}
		if ((st = lex(fd, tok, it, ln)))
			return (st);
		if (!i && (tok->id == TOK_EOL || tok->id == TOK_END))
			break ;
		if (ft_strchr("({[", tok->id))
			stack[i++] = sh_isbracket(tok->id);
		else if (i && tok->id == stack[i - 1])
			--i;
		else if (ft_strchr(")}]", tok->id) && (!i || tok->id != stack[i - 1]))
			return (i ? sh_synerr(*ln, *ln + tok->pos, UNXPTD_C, tok->id,
				stack[i - 1]) : sh_synerr(*ln, *ln + tok->pos, UXPTD, tok->id));
	}
	return (tok ? sh_lexreduce(fd, toks, it, ln) : YEP);
}

int					sh_lexnext(int fd, t_deq *toks, char **ln)
{
	char	*it;
	int		st;

	if (fd < 0)
		return (NOP);
	if (!(st = rl_catline(fd, ';', ln, &it)))
		while (!(st = sh_lex(fd, toks, &it, ln)))
			;
	return (st);
}
