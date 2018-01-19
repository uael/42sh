/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

inline int	rl_signalc(void)
{
    g_eln->idx = 0;
    g_eln->str.len = 0;
    *g_eln->str.buf = '\0';
    ft_write(STDOUT_FILENO, "^C\n", 3);
    rl_editprint();
    return (YEP);
}

inline int	rl_signald(void)
{
    if (g_eln->str.len)
        return (YEP);
    ft_sdsmpush(&g_eln->str, "exit", 4);
    rl_editprint();
    ft_write(STDOUT_FILENO, "\n", 1);
    return (RL_EXIT);
}