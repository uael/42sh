/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_PS_BI_H
# define USH_PS_BI_H

# include <librl.h>

# include "proc.h"

extern int	ps_bibg(int ac, char **av, char **env);
extern int	ps_bifg(int ac, char **av, char **env);
extern int	ps_bijobs(int ac, char **av, char **env);

#endif
