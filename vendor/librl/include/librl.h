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

struct s_rl;

extern int	rl_ctor(struct s_rl *self, int ifd, int ofd, t_bool ml);
extern void	rl_dtor(struct s_rl *self);

extern int	rl_hist_load(struct s_rl *self, char const *filename);
extern int	rl_hist_save(struct s_rl *self, char const *filename);

extern char	*rl_readline(struct s_rl *self, char const *prompt);
extern char	*rl_readnext(struct s_rl *self, char const *prompt);

#endif
