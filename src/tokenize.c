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

#include "msh/tokenize.h"

static inline int	tok_opmatch(t_tok *tok, char **ln, uint8_t len, uint8_t id)
{
	tok->id = id;
	tok->val = *ln;
	*ln += len;
	tok->len += len;
	return (YEP);
}

static inline int	tok_op(t_tok *tok, char **ln)
{
	if ((*ln)[0] == '>' && (*ln)[1] == '>' && (*ln)[2] == '-')
		return (tok_opmatch(tok, ln, 3, TOK_HEREDOCT));
	else if ((*ln)[0] == '>' && (*ln)[1] == '>')
		return (tok_opmatch(tok, ln, 2, TOK_RAOUT));
	else if ((*ln)[0] == '&' && (*ln)[1] == '>')
		return (tok_opmatch(tok, ln, 2, TOK_AMPR));
	else if ((*ln)[0] == '>' && (*ln)[1] == '&')
		return (tok_opmatch(tok, ln, 2, TOK_RAMP));
	else if ((*ln)[0] == '>' && (*ln)[1] == '|')
		return (tok_opmatch(tok, ln, 2, TOK_RPOUT));
	else if ((*ln)[0] == '|' && (*ln)[1] == '|')
		return (tok_opmatch(tok, ln, 2, TOK_LOR));
	else if ((*ln)[0] == '<' && (*ln)[1] == '>')
		return (tok_opmatch(tok, ln, 2, TOK_CMP));
	else if ((*ln)[0] == '<' && (*ln)[1] == '<')
		return (tok_opmatch(tok, ln, 2, TOK_HEREDOC));
	else if ((*ln)[0] == '<' && (*ln)[1] == '&')
		return (tok_opmatch(tok, ln, 2, TOK_LAMP));
	else if ((*ln)[0] == '&' && (*ln)[1] == '&')
		return (tok_opmatch(tok, ln, 2, TOK_LAND));
	else if ((*ln)[0] == '>' || (*ln)[0] == '<')
		return (tok_opmatch(tok, ln, 1, (uint8_t) (*ln)[0]));
	return (NOP);
}

static inline int	tok_quote(int fd, char **ln, char *word, uint16_t i)
{
	char quote;

	quote = *(*ln)++;
	while (1)
		if (!**ln && !(*ln = sh_readcat(fd, "> ", '\n')))
			return (WUT);
		else if (quote == '"' && *(*ln - 1) == '\\')
			word[i++] = ft_strchr("\\\n\"$", **ln) ? *(*ln)++ : (char)'\\';
		else if (quote == '\'' && *(*ln - 1) == '\\')
			word[i++] = **ln == '\'' ? *(*ln)++ : (char)'\\';
		else if (**ln == quote && ++*ln)
			break ;
		else if (**ln == '\\')
			++*ln;
		else
			word[i++] = *(*ln)++;
	return (i);
}

static inline int	tok_word(int fd, t_tok *tok, char **ln)
{
	char		word[LN_MAX];
	uint16_t	i;
	int			st;

	i = 0;
	if (tok->len)
		word[i++] = *tok->val;
	while (**ln && **ln != ' ' && **ln != '\n')
		if (**ln == '\'' || **ln == '"')
		{
			if ((st = tok_quote(fd, ln, word, i)) < 0)
				return (WUT);
			i = (uint16_t)st;
		}
		else if (**ln == '\\' && *++*ln == '\n' && !*++*ln &&
			!(*ln = sh_readcat(fd, "> ", -1)))
			return (WUT);
		else
			word[i++] = *(*ln)++;
	if (!(tok->len = i))
		return (NOP);
	tok->id = TOK_WORD;
	tok->val = ft_memcpy(ft_malloc(i * sizeof(char)), word, i);
	tok->val[i] = '\0';
	return (YEP);
}

int					sh_tokenize(int fd, t_deq *toks, char *ln)
{
	t_tok		*tok;
	
	ft_deqclean(toks, NULL);
	while (*ln)
	{
		tok = ft_deqpush(toks);
		while (*ln == ' ' || *ln == '\t')
			++ln;
		if ((tok->len = (size_t)ft_isdigit(*ln)))
			++ln;
		if (tok_op(tok, &ln) && tok_word(fd, tok, &ln))
		{
			if (ft_strchr("=!()-;[]{|}\n", *ln))
				tok_opmatch(tok, &ln, 1, (uint8_t)*ln);
			else
				return (ENO_THROW(WUT, EINVAL));
		}
	}
	return (YEP);
}
