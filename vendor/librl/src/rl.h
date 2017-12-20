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

extern char		*rl_throw(int eno);

extern int		rl_edit(t_rl *self);
extern void		rl_refresh(t_rl *self);

extern void		rl_move_home(t_rl *self);
extern void		rl_move_end(t_rl *self);
extern void		rl_move_left(t_rl *self);
extern void		rl_move_right(t_rl *self);
extern void		rl_move_prev(t_rl *self);
extern void		rl_move_up(t_rl *self);
extern void		rl_move_down(t_rl *self);
extern void		rl_move_next(t_rl *self);

extern int		rl_cursor(int ifd, int ofd);
extern int		rl_cols(int ifd, int ofd);

extern void		rl_hist_next(t_rl *self, int dir);

#endif
