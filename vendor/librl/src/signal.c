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
    while (g_eln->idx && g_eln->str.len)
    {
        ft_sdsrem(&g_eln->str, --g_eln->idx, NULL);
    }
    ft_write(STDOUT_FILENO, "\n", 1);
    rl_editprint();
    return (YEP);
}

inline int	rl_signald(void)
{
    return 1;
}