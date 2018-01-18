/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/proc/state.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PROC_STATE_H
# define USH_PROC_STATE_H

# include "../shell.h"

typedef enum	e_procst
{
	PROC_NEW,
	PROC_COMPLETED,
	PROC_TERMINATED,
	PROC_STOPPED,
	PROC_RUNNING,
	PROC_CONTINUED
}				t_procst;

#endif
