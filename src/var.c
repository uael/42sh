/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/env.h"

inline void		sh_varctor(t_map *vars)
{
	ft_mapctor(vars, g_strhash, sizeof(char *), sizeof(char *));
}

inline void		sh_vardtor(t_map *vars)
{
	ft_mapdtor(vars, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

inline void		sh_varset(t_map *vars, char *var, char *val)
{
	uint32_t	it;

	if (ft_mapget(vars, var, &it) || ft_mapput(vars, ft_strdup(var), &it))
		((char **)vars->vals)[it] = ft_strdup(val);
}

inline char		*sh_varget(t_map *vars, char *var)
{
	uint32_t	it;

	if (ft_mapget(vars, var, &it))
		return (((char **)vars->vals)[it]);
	return (NULL);
}
