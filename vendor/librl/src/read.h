/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:13:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_READ_H
# define LIBRL_READ_H

# include <signal.h>

# include "edit.h"

typedef enum	e_rmode
{
	RL_NONE,
	RL_OFF,
	RL_INSERT,
	RL_SEARCH,
	RL_VISUAL
}				t_rmode;

extern t_rmode	g_mode;
extern TTY		g_orig_mode;
extern TTY		g_raw_mode;

extern int		rl_readnotty(int fd, char **ln);
extern void		rl_ttyfinalize(int fd);
extern void		rl_ttydtor(void);
extern void		rl_nottyfinalize(int fd);
extern void		rl_nottydtor(void);
extern int		rl_rawmode(int fd);
extern int		rl_offmode(int fd);

#endif
