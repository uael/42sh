/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:05:04 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/edit.h"
#include "msh/shell.h"

static char			g_caps[32][6] = { { 0 } };
static int8_t		g_caps_init[32] = { 0 };
static char			*g_caps_names[32] =
{
	[CAPS_U7] = "u7",
	[CAPS_CM] = "cm",
	[CAPS_LE] = "le",
	[CAPS_ND] = "nd",
	[CAPS_CD] = "cd",
	[CAPS_CE] = "ce",
};

static inline char	*loadcaps(uint8_t id)
{
	char *ret;

	if (g_caps_init[id] == 1)
		return (g_caps[id]);
	if (g_caps_init[id] == -1)
		return (NULL);
	if ((ret = tgetstr(g_caps_names[id], (char **)&g_caps[id])))
		g_caps_init[id] = -1;
	else
		g_caps_init[id] = 1;
	return (ret);
}

inline t_bool		sh_getcaps(uint8_t id, char **ret)
{
	if (g_hastc && (*ret = loadcaps(id)))
		return (1);
	return (0);
}
