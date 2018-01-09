/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex/heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/lex.h"

static inline char	*heredoc(t_tok *tok, size_t *eofl)
{
	char	*eof;

	*eofl = tok->len;
	eof = ft_memcpy(ft_malloc(*eofl * sizeof(char)), tok->val, tok->len);
	tok->len = 0;
	return (eof);
}

static inline int	finalize(char **it, char **ln, char *beg, char *eof)
{
	free(eof);
	*it = *ln + (*it - beg);
	return (YEP);
}

inline int			sh_lexheredoc(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eol;
	char	*eof;
	char	*beg;
	size_t	eofl;

	beg = *ln;
	if (!(eol = ft_strchr(*it, '\n')))
		return (ENO_THROW(WUT, EINVAL));
	eof = heredoc(tok, &eofl);
	while (++eol)
		if (!*eol && (fd < 0 || !(eol = sh_readcat(fd, "> ", 0, ln))))
			return (ENO_THROW(WUT, EINVAL));
		else if (*ft_sdscpush((t_sds *)tok, *eol) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n' &&
			!ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	return (finalize(it, ln, beg, eof));
}

inline int			sh_lexheredoct(int fd, t_tok *tok, char **it, char **ln)
{
	char	*eol;
	char	*eof;
	char	*beg;
	size_t	eofl;

	beg = *ln;
	if (!(eol = ft_strchr(*it, '\n')))
		return (ENO_THROW(WUT, EINVAL));
	eof = heredoc(tok, &eofl);
	while (++eol)
	{
		if (!*eol && (fd < 0 || !(eol = sh_readcat(fd, "> ", 0, ln))))
			return (ENO_THROW(WUT, EINVAL));
		if (*(eol - 1) == '\n')
			while (*eol == '\t')
				++eol;
		if (*ft_sdscpush((t_sds *)tok, *eol) == '\n' && tok->len >=
			eofl + 2 && tok->val[tok->len - (eofl + 2)] == '\n' &&
			!ft_strncmp(tok->val + tok->len - (eofl + 1), eof, eofl))
		{
			ft_sdsnpop((t_sds *)tok, eofl + 1, NULL);
			break ;
		}
	}
	return (finalize(it, ln, beg, eof));
}
