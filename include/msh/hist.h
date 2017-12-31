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

# include "sh.h"
# include "lex.h"

#define LN_MAX (2048)
#define HIST_MAX (100)

typedef struct	s_editln
{
	char		buf[LN_MAX];
	uint16_t	idx;
	uint16_t	len;
}				t_editln;

typedef struct	s_histln
{
	char		*buf;
	uint16_t	len;
	uint16_t	cap;
	t_editln	edit;
}				t_histln;

extern t_histln	g_hist[HIST_MAX];
extern uint8_t	g_hist_len;
extern uint8_t	g_hist_idx;

extern t_histln	*sh_histln(void);
extern t_histln	*sh_histpush(char const *ln);

#endif
