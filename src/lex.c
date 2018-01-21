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
	return ((ret = g_tokidsstr[tok->id]) ? ret : "<unknown>");
}

static inline int	lex(int fd, t_tok *tok, char **it, char **ln)
{
	int	st;

	tok->len = 0;
	while (ft_strchr(sh_varifs(), **it))
		++*it;
	tok->pos = (uint16_t)(*it - *ln);
	if (**it == '\n' || (**it == '\r' && *(*it + 1) == '\n'))
	{
		tok->id = TOK_EOL;
		ft_sdscpush((t_sds *)tok, '\n');
		while (*++*it == '\n')
			;
		return (YEP);
	}
	while (**it == '\\' && ((*(*it + 1) == '\n' && !*(*it + 2)) ||
		((*(*it + 1) == '\r' && *(*it + 2) == '\n' && !*(*it + 3)))))
		if ((st = fd < 0 ? NOP : rl_catline(fd, -2, ln, it)))
			return (st);
	if (**it == '#')
		while (**it && **it != '\n' && **it != '\r')
			++it;
	if (!**it)
	{
		tok->id = TOK_END;
		return (YEP);
	}
	if (ft_isdigit(**it))
		ft_sdscpush((t_sds *)tok, *(*it)++);
	if ((st = sh_lexop(fd, tok, it, ln)) < 0)
		return (WUT);
	if (st && (st = sh_lexword(fd, tok, it, ln)) < 0)
		return (WUT);
	return (st == NOP ? sh_synerr(*ln, *it, "Unexpected token `%c'", **it)
		: YEP);
}

static inline int	reduce(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok	*tok;
	t_tok	*prev;
	t_tok	*end;

	prev = NULL;
	tok = (t_tok *)ft_deqbeg(toks) - 1;
	end = ft_deqend(toks);
	while (++tok < end)
	{
		if (tok->id == TOK_WORD && prev)
		{
			if (prev->id == TOK_HEREDOC && sh_lexheredoc(fd, tok, it, ln))
				return (WUT);
			if (prev->id == TOK_HEREDOCT && sh_lexheredoct(fd, tok, it, ln))
				return (WUT);
		}
		else if (prev && (prev->id == TOK_HEREDOC || prev->id == TOK_HEREDOCT))
			return (sh_synerr(*ln, *ln + tok->pos, "Expected `%s' after "
				"heredoc `%s' got `%s'", sh_tokidstr(TOK_WORD),
				sh_tokidstr(prev->id), sh_tokidstr(tok->id)));
		prev = tok;
	}
	return (YEP);
}

char				bracket(char b)
{
	if (b == '[')
		return ']';
	if (b == '{')
		return '}';
	if (b == '(')
		return ')';
	return (0);
}

int					sh_lex(int fd, t_deq *toks, char **it, char **ln)
{
	t_tok	*tok;
	int 	st;
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
			stack[i++] = bracket(tok->id);
		else if (i && tok->id == stack[i - 1])
			--i;
		else if (ft_strchr(")}]", tok->id) && (!i || tok->id != stack[i - 1]))
		{
			if (i)
				return (sh_synerr(*ln, *ln + tok->pos, "Unexpected token `%c' "
					"while looking for matching `%c'", tok->id, stack[i - 1]));
			return (sh_synerr(*ln, *ln + tok->pos, "Unexpected closing "
				"bracket `%c'", tok->id));
		}
	}
	return (tok ? reduce(fd, toks, it, ln) : YEP);
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
