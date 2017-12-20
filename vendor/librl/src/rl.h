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

# include "librl.h"

typedef int		(t_rl_keyc)(t_rl *self, char const *key, int rd);

typedef struct	s_rl_bind
{
	int			rd;
	char const	*key;
	t_rl_keyc	*cb;
}				t_rl_bind;

extern int		rl_edit(t_rl *self);
extern void		rl_refresh(t_rl *self);

extern void		rl_move_prev(t_rl *self);
extern void		rl_move_down(t_rl *self);
extern void		rl_move_next(t_rl *self);

extern int		rl_cursor(int ifd, int ofd);
extern int		rl_cols(int ifd, int ofd);

extern void		rl_hist_next(t_rl *self, int dir);

#endif
