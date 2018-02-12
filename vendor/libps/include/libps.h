/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_H
# define LIBPS_H

# include <libft.h>

#include "libps/job.h"
#include "libps/proc.h"
#include "libps/redir.h"

typedef int		(t_errcb)(char const *fmt, ...);
typedef int		(t_fatalcb)(int code, char const *fmt, ...);

extern void		ps_read(t_sds *dst, t_proccb *cb, t_dtor dtor, void *data);
extern int		ps_init(int fd, t_errcb *errcb, t_fatalcb *fatalcb);
extern void		ps_dtor(void);
extern pid_t	ps_lastpid(void);

#endif