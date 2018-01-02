/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EDIT_H
# define MSH_EDIT_H

# include <termios.h>

# include "screen.h"

# ifndef TTY
#  define TTY struct termios
# endif

# define LN_MAX (2048)

typedef struct	s_editln
{
	char		buf[LN_MAX];
	uint16_t	idx;
	uint16_t	len;
}				t_editln;

extern int		sh_editln(t_editln *ln, char *prompt, size_t plen);

#endif
