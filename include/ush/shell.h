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

#define SHLVL_MAX 255

enum			e_opts
{
	OPT_a = 1 << 1,
	OPT_b = 1 << 2,
	OPT_C = 1 << 3,
	OPT_e = 1 << 4,
	OPT_f = 1 << 5,
	OPT_m = 1 << 6,
	OPT_n = 1 << 7,
	OPT_u = 1 << 9,
	OPT_v = 1 << 10,
	OPT_x = 1 << 11
};

typedef struct	s_scope
{
	int			ac;
	char		**av;
	int			status;
	uint16_t	opts;
	pid_t		pid;
	pid_t		ppid;
	t_bool		interact;
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
