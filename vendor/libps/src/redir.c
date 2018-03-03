/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

static void		redirectscope(t_redirs *redirs, int *scope)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < redirs->len)
	{
		redir = redirs->buf + i++;
		if (scope && redir->from >= 0 && redir->from <= 2 &&
			scope[redir->from] < 0)
			scope[redir->from] = dup(redir->from);
	}
}

inline int		ps_redirect(t_redirs *redirs, int *scope)
{
	size_t	i;
	t_redir	*redir;

	redirectscope(redirs, scope);
	i = 0;
	while (i < redirs->len)
	{
		redir = redirs->buf + i++;
		if (redir->kind == 2)
			return (g_errcb("%s: ambiguous redirect\n", redir->word));
		else if (redir->kind == 1)
		{
			if ((redir->fd = open(redir->word, redir->flags, 0644)) < 0)
				return (g_errcb("%s: %e\n", redir->word, errno));
			dup2(redir->fd, redir->from);
			if (redir->from2 >= 0)
				dup2(redir->fd, redir->from2);
		}
		else if (!ft_strcmp("-", redir->word))
			close(redir->from);
		else if (!ft_isdigit(*redir->word) || ft_strlen(redir->word) != 1)
			return (g_errcb("%s: ambiguous redirect\n", redir->word));
		else
		{
			dup2(redir->fd = *redir->word - '0', redir->from);
			if (redir->from2 >= 0)
				dup2(redir->fd, redir->from2);
		}
	}
	return (YEP);
}

inline void		ps_redirectclose(t_redirs *redirs)
{
	size_t	i;
	t_redir	*redir;

	i = 0;
	while (i < redirs->len)
	{
		if ((redir = redirs->buf + i++)->fd > 2)
			close(redir->fd);
		if (redir->word)
			free(redir->word);
	}
}
