/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 09:49:12 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRL_HIST_H
# define LIBRL_HIST_H

# include "librl.h"

# define HIST_MAX (250)
# define HIST_DELTA (5)

extern t_sds	g_hist[HIST_MAX];
extern uint8_t	g_hist_len;

extern char		*rl_histcat(char const *ln, size_t len, char c, char **out);
extern t_bool	rl_histcpy(uint8_t id, t_sds *dest);
extern t_sds	*rl_histat(ssize_t idx);
extern t_sds	*rl_histback(void);
extern int		rl_histbi(void);

#endif
