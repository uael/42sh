/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/hist.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 09:49:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_HIST_H
# define MSH_HIST_H

# include "edit.h"

# define HIST_MAX (100)

typedef struct	s_histln
{
	char		*buf;
	uint16_t	cap;
	uint16_t	len;
	t_editln	edit;
}				t_histln;

extern t_histln	*sh_histln(void);
extern t_histln	*sh_histpush(char const *ln);

#endif
