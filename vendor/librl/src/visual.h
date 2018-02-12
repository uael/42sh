/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:13:28 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_VISUAL_H
# define LIBRL_VISUAL_H

# include "edit.h"

extern void		rl_visualdtor(void);
extern int		rl_visualtoggle(void);
extern int		rl_visualyank(void);
extern int		rl_visualdelete(void);
extern int		rl_visualpaste(void);

#endif
