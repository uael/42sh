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

# define SHLVL_MAX 255

typedef struct	s_scope
{
	int			ac;
	char		**av;
	int			status;
	pid_t		pid;
	pid_t		ppid;
	t_bool		tty;
}				t_scope;

extern t_scope	*g_sh;
extern uint8_t	g_shlvl;
extern TTY		g_shmode;
extern int		g_shfd;

extern uint8_t	sh_scope(void);
extern uint8_t	sh_unscope(void);
extern char		*sh_prompt(char *prompt, char *buf);
extern int		sh_run(int fd, char *ln);
extern int		sh_exit(int exitno, char const *fmt, ...);
extern void		sh_complete(t_sds *cmd);

#endif
