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

#include "ush/redir.h"

static inline int	redirect(t_redir *r)
{
	while (1)
	{
		if (r->filename && !ft_strcmp("-", r->filename))
			r->to = -1;
		else if (r->filename && (r->to = open(r->filename, r->flags, 0644)) < 0)
			break ;
		else if (r->to == -1 && close(r->to))
			break ;
		else if (r->to >= 0 && dup2(r->to, r->from) < 0)
			break ;
		else if (r->to > 2)
			close(r->to);
		return (YEP);
	}
	return (!r->tok || !r->ln ? sh_err("%s: %e", r->filename, errno) :
		sh_evalerr(r->ln, r->tok, "%s: %e", r->filename, errno));
}

inline int			sh_redirect(t_redirs *redirs, int *scope)
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
	i = 0;
	while (i < redirs->len)
		if (redirect(redirs->buf + i++))
			return (OUF);
	return (YEP);
}
