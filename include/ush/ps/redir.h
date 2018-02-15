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

#ifndef LIBPS_REDIR_H
# define LIBPS_REDIR_H

# include <libft.h>

typedef struct	s_redir
{
	int			to;
	int			from;
}				t_redir;

typedef struct	s_redirs
{
	t_redir		*buf;
	size_t		isz;
	size_t		cap;
	size_t		len;
}				t_redirs;

#endif
