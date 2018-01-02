/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/screen.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SCREEN_H
# define MSH_SCREEN_H

# include <libft.h>
# include <sys/ioctl.h>

extern uint16_t g_cols;
extern uint16_t g_pos;

extern int		sh_screenpos(int ifd, int ofd);
extern int		sh_screenwidth(int ifd, int ofd);

#endif
