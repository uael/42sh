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
	ft_sdsmpush((t_sds *)tok, *str, len);
	*str += len;
	return (YEP);
}

static inline int	tok_op(t_tok *tok, char **str)
{
	if ((*str)[0] == '<' && (*str)[1] == '<' && (*str)[2] == '-')
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
	if (!i)
		return (NOP);
	tok->id = TOK_WORD;
	ft_sdsmpush((t_sds *)tok, word, i);
	return (YEP);
}

static inline int	tok_heredoc(int fd, t_tok *tok, char **str, char *beg)
{
	char	*eol;
	char	*eof;
	size_t	eofl;

	if (!(eol = ft_strchr(*str, '\n')))
		return (ENO_THROW(WUT, EINVAL));
	eofl = tok->len;
	eof = ft_memcpy(ft_malloc(eofl * sizeof(char)), tok->val, tok->len);
	tok->len = 0;
	while (++eol)
		if (!*eol && (fd < 0 || !(eol = sh_readcat(fd, "> ", 0))))
			return (ENO_THROW(WUT, EINVAL));
		else if (*ft_sdscpush((t_sds *)tok, *eol) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n')
		{
			if (ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
				continue ;
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	free(eof);
	if (fd >= 0)
		*str = sh_histln()->buf + (*str - beg);
	return (YEP);
}

static inline int	tok_heredoct(int fd, t_tok *tok, char **str, char *beg)
{
	char	*eol;
	char	*eof;
	size_t	eofl;

	if (!(eol = ft_strchr(*str, '\n')))
		return (ENO_THROW(WUT, EINVAL));
	eofl = tok->len;
	eof = ft_memcpy(ft_malloc(eofl * sizeof(char)), tok->val, tok->len);
	tok->len = 0;
	while (++eol)
	{
		if (!*eol && (fd < 0 || !(eol = sh_readcat(fd, "> ", 0))))
			return (ENO_THROW(WUT, EINVAL));
		if (*(eol - 1) == '\n')
			while (*eol == '\t')
				++eol;
		if (*ft_sdscpush((t_sds *)tok, *eol) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n')
		{
			if (ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
				continue ;
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	}
	free(eof);
	if (fd >= 0)
		*str = sh_histln()->buf + (*str - beg);
	return (YEP);
}

int					sh_tokenize(int fd, t_deq *toks, char *str)
{
	t_tok	*tok;
	t_tok	*prev;
	char	*beg;

	prev = NULL;
	toks->len = 0;
	toks->cur = 0;
	beg = str;
	while (*str)
	{
		tok = ft_deqpush(toks);
		while (*str == ' ' || *str == '\t')
			++str;
		tok->len = 0;
		if (*str == '\n')
			return (tok_opmatch(tok, &str, 1, TOK_EOL));
		if (ft_isdigit(*str))
			ft_sdscpush((t_sds *)tok, *str++);
		if (tok_op(tok, &str) && tok_word(fd, tok, &str))
		{
			if (ft_strchr("=!()-;[]{|}", *str))
				tok_opmatch(tok, &str, 1, (uint8_t)*str);
			else
				return (ENO_THROW(WUT, EINVAL));
		}
		else if (prev && prev->id == TOK_HEREDOC && tok->id == TOK_WORD &&
			tok_heredoc(fd, tok, &str, beg))
			return (WUT);
		else if (prev && prev->id == TOK_HEREDOCT && tok->id == TOK_WORD &&
			tok_heredoct(fd, tok, &str, beg))
			return (WUT);
		prev = tok;
	}
	return (YEP);
}

inline void			sh_tokdtor(t_tok *tok)
{
	if (tok->val)
		free(tok->val);
	FT_INIT(tok, t_tok);
}
