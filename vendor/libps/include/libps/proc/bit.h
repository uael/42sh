/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/proc/bit.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_PROC_BIT_H
# define LIBPS_PROC_BIT_H

# include <libft.h>

struct s_proc;

typedef t_bool	t_procbit;

extern void		ps_procbit(struct s_proc *proc, t_bool bit);

#endif
