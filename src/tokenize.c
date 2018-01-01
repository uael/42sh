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

static inline int	tok_opmatch(t_tok *tok, char **str, uint8_t len, uint8_t id)
{
	tok->id = id;
	tok->val = *str;
	*str += len;
	tok->len += len;
	return (YEP);
}

static inline int	tok_op(t_tok *tok, char **str)
{
	if ((*str)[0] == '>' && (*str)[1] == '>' && (*str)[2] == '-')
		return (tok_opmatch(tok, str, 3, TOK_HEREDOCT));
	else if ((*str)[0] == '>' && (*str)[1] == '>')
		return (tok_opmatch(tok, str, 2, TOK_RAOUT));
	else if ((*str)[0] == '&' && (*str)[1] == '>')
		return (tok_opmatch(tok, str, 2, TOK_AMPR));
	else if ((*str)[0] == '>' && (*str)[1] == '&')
		return (tok_opmatch(tok, str, 2, TOK_RAMP));
	else if ((*str)[0] == '>' && (*str)[1] == '|')
		return (tok_opmatch(tok, str, 2, TOK_RPOUT));
	else if ((*str)[0] == '|' && (*str)[1] == '|')
		return (tok_opmatch(tok, str, 2, TOK_LOR));
	else if ((*str)[0] == '<' && (*str)[1] == '>')
		return (tok_opmatch(tok, str, 2, TOK_CMP));
	else if ((*str)[0] == '<' && (*str)[1] == '<')
		return (tok_opmatch(tok, str, 2, TOK_HEREDOC));
	else if ((*str)[0] == '<' && (*str)[1] == '&')
		return (tok_opmatch(tok, str, 2, TOK_LAMP));
	else if ((*str)[0] == '&' && (*str)[1] == '&')
		return (tok_opmatch(tok, str, 2, TOK_LAND));
	else if ((*str)[0] == '>' || (*str)[0] == '<')
		return (tok_opmatch(tok, str, 1, (uint8_t) (*str)[0]));
	return (NOP);
}

static inline int	tok_quote(int fd, char **str, char *word, uint16_t i)
{
	char quote;

	quote = *(*str)++;
	while (1)
		if (!**str && (fd < 0 || !(*str = sh_readcat(fd, "> ", '\n'))))
			return (WUT);
		else if (quote == '"' && *(*str - 1) == '\\')
			word[i++] = ft_strchr("\\\n\"$", **str) ? *(*str)++ : (char)'\\';
		else if (quote == '\'' && *(*str - 1) == '\\')
			word[i++] = **str == '\'' ? *(*str)++ : (char)'\\';
		else if (**str == quote && ++*str)
			break ;
		else if (**str == '\\')
			++*str;
		else
			word[i++] = *(*str)++;
	return (i);
}

static inline int	tok_word(int fd, t_tok *tok, char **str)
{
	char		word[LN_MAX];
	uint16_t	i;
	int			st;

	i = 0;
	if (tok->len)
		word[i++] = *tok->val;
	while (**str && **str != ' ' && **str != '\n')
		if (**str == '\'' || **str == '"')
		{
			if ((st = tok_quote(fd, str, word, i)) < 0)
				return (WUT);
			i = (uint16_t)st;
		}
		else if (**str == '\\' && *++*str == '\n' && !*++*str &&
			(fd < 0 || !(*str = sh_readcat(fd, "> ", -1))))
			return (WUT);
		else
			word[i++] = *(*str)++;
	if (!(tok->len = i))
		return (NOP);
	tok->id = TOK_WORD;
	tok->val = ft_memcpy(ft_malloc(i * sizeof(char)), word, i);
	tok->val[i] = '\0';
	return (YEP);
}

int					sh_tokenize(int fd, t_deq *toks, char *str)
{
	t_tok		*tok;
	t_tok		*prev;

	prev = NULL;
	ft_deqclean(toks, NULL);
	while (*str)
	{
		tok = ft_deqpush(toks);
		while (*str == ' ' || *str == '\t')
			++str;
		if ((tok->len = (size_t)ft_isdigit(*str)))
			++str;
		if (tok_op(tok, &str) && tok_word(fd, tok, &str))
		{
			if (ft_strchr("=!()-;[]{|}\n", *str))
				tok_opmatch(tok, &str, 1, (uint8_t)*str);
			else
				return (ENO_THROW(WUT, EINVAL));
		}
		else if (prev && prev->id == TOK_HEREDOC && tok->id == TOK_WORD)
		{

		}
		prev = tok;
	}
	return (YEP);
}
