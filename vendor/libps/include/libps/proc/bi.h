/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libps/proc/bi.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPS_PROC_BI_H
# define LIBPS_PROC_BI_H

# include <libft.h>

struct s_proc;

typedef int		(t_procbi)(int ac, char **av, char **envv);

extern void		ps_biregister(char const *name, t_procbi *fn);

#endif

