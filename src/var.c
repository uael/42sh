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

#include "ush/var.h"

static t_map	g_locals_stack =
{
	0, 0, 0, 0, NULL, { (t_hashfn *)ft_strhash, (t_eqfn *)ft_streq },
	sizeof(char *), sizeof(char *), NULL, NULL
};
static t_map	*g_locals = &g_locals_stack;

inline int		sh_vardump(char **envv)
{
	uint32_t	it;
	char		*val;

	it = 0;
	if (envv)
		while (*envv)
			ft_putl(STDOUT_FILENO, *envv++);
	while (it < g_locals->cap)
	{
		if (BUCKET_ISPOPULATED(g_locals->bucks, it))
		{
			val = ((char **)g_locals->vals)[it];
			ft_putf(STDOUT_FILENO, ft_strlen(val) ? "%s=%s\n" : "%s=''\n",
				((char **)g_locals->keys)[it], val);
		}
		++it;
	}
	return (YEP);
}

inline void		sh_vardtor(void)
{
	ft_mapdtor(g_locals, (t_dtor)ft_pfree, (t_dtor)ft_pfree);
}

inline void		sh_varset(char *var, char *val)
{
	uint32_t	it;
	char		*dvar;

	if (val && sh_getenv(var))
		sh_setenv(var, val);
	else if (!val)
	{
		if (ft_mapget(g_locals, var, &it))
		{
			free(((char **)g_locals->keys)[it]);
			free(((char **)g_locals->vals)[it]);
			ft_mapdel(g_locals, it);
		}
	}
	else if (ft_mapget(g_locals, var, &it))
	{
		free(((char **)g_locals->vals)[it]);
		((char **)g_locals->vals)[it] = ft_strdup(val);
	}
	else if (ft_mapput(g_locals, dvar = ft_strdup(var), &it))
		((char **)g_locals->vals)[it] = ft_strdup(val);
	else
		free(dvar);
}

inline char		*sh_varget(char *var, char **envv)
{
	uint32_t	it;

	if (ft_mapget(g_locals, var, &it))
		return (((char **)g_locals->vals)[it]);
	return (envv ? ft_getenv(envv, var) : NULL);
}

inline char		*sh_varifs(void)
{
	static char	*ifs = NULL;
	char		*eol;

	if (ifs)
		return (ifs);
	if (!(ifs = sh_getenv("IFS")))
		ifs = SH_IFS;
	else if ((eol = ft_strchr(ifs, '\n')))
		*eol = ' ';
	return (ifs);
}
