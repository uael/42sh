/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 07:00:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_H
# define LIBRL_H

# include <libft.h>
# include <termios.h>

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
	RL_SEARCH,
	RL_VISUAL
}				t_rl_mode;

typedef struct	s_rl_hist
{
	char		**buf;
	int			len;
	int			max;
	int			idx;
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
	int			mlen;
	int			len;
	const char	*prompt;
	int			plen;
	int			pos;
	int			oldpos;
	int			mrows;
	int			cols;
	uint8_t		ml;
	t_rl_hist	hist;
}				t_rl;

extern int		rl_ctor(t_rl *self, int ifd, int ofd, t_bool ml);
extern void		rl_dtor(t_rl *self);

extern int		rl_hist_load(t_rl *self, char const *filename);
extern int		rl_hist_save(t_rl *self, char const *filename);
extern char		*rl_hist_add(t_rl *self, char const *line);

extern char		*rl_readline(t_rl *self, char const *prompt);
extern char		*rl_readnext(t_rl *self, char const *prompt);

#endif
