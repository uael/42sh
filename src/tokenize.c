/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static inline void	lex_match(t_sh_tok *tok, char **ln, uint8_t len, uint8_t id)
{
	tok->id = id;
	*ln += len;
	tok->len += len;
}

inline int	tok_sinquote(char **ln, char *word, uint16_t i)
{
	++*ln;
	while (1)
		if (!**ln)
		{
			if (!(*ln = sh_readcat(0, "> ", '\n')))
				return (WUT);
		}
		else if (*(*ln - 1) == '\\')
		{
			if (**ln == '\'')
				word[i++] = *(*ln)++;
			else
				word[i++] = '\\';
		}
		else if (**ln == '\'')
		{
			++*ln;
			break ;
		}
		else if (**ln == '\\')
			++*ln;
		else
			word[i++] = *(*ln)++;
	return (i);
}

inline int	tok_dblquote(char **ln, char *word, uint16_t i)
{
	++*ln;
	while (1)
		if (!**ln)
		{
			if (!(*ln = sh_readcat(0, "> ", '\n')))
				return (WUT);
		}
		else if (*(*ln - 1) == '\\')
		{
			if (ft_strchr("\\\n\"$", **ln))
				word[i++] = *(*ln)++;
			else
				word[i++] = '\\';
		}
		else if (**ln == '\"')
		{
			++*ln;
			break ;
		}
		else if (**ln == '\\')
			++*ln;
		else
			word[i++] = *(*ln)++;
	return (i);
}

int	sh_tokenize(t_deq *toks, char *ln)
{
	t_sh_tok	*tok;
	t_sh_tok	*prev;
	char		word[LN_MAX];
	uint16_t	i;
	int			st;
	
	ft_deq_clean(toks, NULL);
	i = 0;
	prev = NULL;
	while (*ln)
	{
		tok = ft_deq_push(toks);
		while (*ln == ' ' || *ln == '\t')
			++ln;
		tok->val = ln;
		tok->len = 0;
		if (ft_isdigit(*ln))
		{
			++ln;
			++tok->len;
		}
		tok->len = (size_t)ft_isdigit(*ln);
		if (ln[0] == '>' && ln[1] == '>' && ln[2] == '-')
			lex_match(tok, &ln, 3, SH_TOK_HEREDOCT);
		else if (ln[0] == '>' && ln[1] == '>')
			lex_match(tok, &ln, 2, SH_TOK_RAOUT);
		else if (ln[0] == '&' && ln[1] == '>')
			lex_match(tok, &ln, 2, SH_TOK_AMPR);
		else if (ln[0] == '>' && ln[1] == '&')
			lex_match(tok, &ln, 2, SH_TOK_RAMP);
		else if (ln[0] == '>' && ln[1] == '|')
			lex_match(tok, &ln, 2, SH_TOK_RPOUT);
		else if (ln[0] == '|' && ln[1] == '|')
			lex_match(tok, &ln, 2, SH_TOK_LOR);
		else if (ln[0] == '<' && ln[1] == '>')
			lex_match(tok, &ln, 2, SH_TOK_CMP);
		else if (ln[0] == '<' && ln[1] == '<')
		{
			lex_match(tok, &ln, 2, SH_TOK_HEREDOC);
		}
		else if (ln[0] == '<' && ln[1] == '&')
			lex_match(tok, &ln, 2, SH_TOK_LAMP);
		else if (ln[0] == '&' && ln[1] == '&')
			lex_match(tok, &ln, 2, SH_TOK_LAND);
		else if (ln[0] == '>' || ln[0] == '<')
			lex_match(tok, &ln, 1, (uint8_t)ln[0]);
		else
		{
			if (tok->len)
				word[i++] = *tok->val;
			while (*ln != ' ')
			{
				if (*ln == '\'')
				{
					if ((st = tok_sinquote(&ln, word, i)) < 0)
						return (WUT);
					i = (uint16_t)st;
				}
				else if (*ln == '"')
				{
					if ((st = tok_dblquote(&ln, word, i)) < 0)
						return (WUT);
					i = (uint16_t)st;
				}
				else
					word[i++] = *ln++;
			}

		}
	}
}
