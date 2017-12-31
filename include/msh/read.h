/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/read.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_READ_H
# define MSH_READ_H

# include <termios.h>
# include <sys/ioctl.h>

# include "hist.h"

# ifndef TTY
#  define TTY struct termios
# endif

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
extern uint16_t g_cols;
extern uint16_t g_pos;

extern char		*sh_readln(int fd, char *prompt);
extern char		*sh_readcat(int fd, char *prompt, char c);
extern char		*sh_readnotty(int fd);
extern int		sh_rawmode(int fd);
extern int		sh_offmode(int fd);
extern int		sh_screenpos(int ifd, int ofd);
extern int		sh_screenwidth(int ifd, int ofd);

#endif
