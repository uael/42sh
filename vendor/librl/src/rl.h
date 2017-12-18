/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_H
# define RL_H

# include <termios.h>
# include "librl.h"

# define RL_MAX_LINE (4096)
# ifndef TTY
#  define TTY struct termios
# endif

typedef TTY		t_termios;

typedef enum	e_rl_mode
{
	RL_OFF,
	RL_NOTTY,
	RL_INSERT,
	RL_VISUAL
}				t_rl_mode;

typedef struct	s_rl_hist
{
	char		**buf;
	size_t		len;
	size_t		max;
	size_t		idx;
	int8_t		search;
}				t_rl_hist;

typedef struct	s_rl
{
	t_rl_mode	mode;
	t_termios	raw;
	t_termios	orig;
	int			ifd;
	int			ofd;
	char		*buf;
	size_t		buflen;
	size_t		len;
	const char	*prompt;
	size_t		plen;
	size_t		pos;
	int			cols;
	uint8_t		ml;
	t_rl_hist	hist;
}				t_rl;


#endif
