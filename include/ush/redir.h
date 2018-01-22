/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/redir.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_REDIR_H
# define USH_REDIR_H

# include "lex.h"
# include "env.h"

typedef struct	s_redir
{
	int			from;
	int			to;
}				t_redir;

typedef struct	s_redirs
{
	t_redir		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
}				t_redirs;

extern int		sh_redirect(t_redirs *redirs, int *scope);

#endif
