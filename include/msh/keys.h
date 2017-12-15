/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/keys.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_KEYS_H
# define MSH_KEYS_H

# include "tc.h"
# include "sh.h"

typedef int		(*t_keys_cb)(t_sh *self, t_tc *tc);

typedef struct	s_keys_hdl
{
	char		*key;
	t_keys_cb	cb;
}				t_keys_hdl;

extern int	sh_keys(t_tc *tc, char *in);
extern int	sh_keys_backspace(t_sh *self, t_tc *tc);
extern int	sh_keys_delete(t_sh *self, t_tc *tc);
extern int	sh_keys_down(t_sh *self, t_tc *tc);
extern int	sh_keys_left(t_sh *self, t_tc *tc);
extern int	sh_keys_return(t_sh *self, t_tc *tc);
extern int	sh_keys_right(t_sh *self, t_tc *tc);
extern int	sh_keys_up(t_sh *self, t_tc *tc);

#endif
