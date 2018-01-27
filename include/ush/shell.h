/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/shell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_SHELL_H
# define USH_SHELL_H

# include "lex.h"
# include "env.h"

extern t_bool	g_shinteract;
extern pid_t	g_shpgid;
extern TTY		g_shmode;
extern int		g_shfd;
extern int		g_shstatus;

extern int		sh_run(int fd, char *ln);
extern int		sh_exit(int exitno, char const *fmt, ...);
extern void		sh_complete(t_sds *cmd);

#endif
