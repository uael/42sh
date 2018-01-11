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

# define HIST_MAX (100)

extern void		rl_histexit(void);
extern char		*rl_histcat(char const *ln, size_t len, char c, char **out);
extern t_bool	rl_histcpy(uint8_t id, t_sds *dest);

#endif
