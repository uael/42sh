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

# include "libps/err.h"
# include "libps/job.h"
# include "libps/pool.h"
# include "libps/proc.h"
# include "libps/redir.h"

extern int		ps_init(int fd, t_errcb *errcb, t_fatalcb *fatalcb);
extern void		ps_dtor(void);
extern pid_t	ps_lastpid(void);

#endif