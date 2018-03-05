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

#include "ush.h"

#define EXPORT_N (1 << 1)
#define EXPORT_F (1 << 2)
#define EXPORT_P (1 << 3)
#define N "export: "

static uint8_t			g_flags = 0;

static inline void		export(char *var, char *val, char **envv)
{
	char *local;

	if (!val && (g_flags & EXPORT_N))
	{
		sh_unsetenv(var, 1);
		return ;
	}
	if ((local = sh_varget(var, envv)) && !val)
		val = local;
	if (!val)
		sh_varset(var, "");
	else
	{
		sh_setenv(var, val);
		if (local)
			sh_varset(var, NULL);
	}
}

static inline int		exportparse(int ac, char *av[])
{
	int opt;

	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "fnp")) != WUT)
		if (opt == 'f')
		{
			if ((g_flags & (EXPORT_P | EXPORT_F | EXPORT_N)))
				return (ft_retf(WUT, N"%c : %e\n", EINVAL));
			g_flags |= EXPORT_F;
		}
		else if (opt == 'n')
		{
			if ((g_flags & (EXPORT_P | EXPORT_F | EXPORT_N)))
				return (ft_retf(WUT, N"%c : %e\n", EINVAL));
			g_flags |= EXPORT_N;
		}
		else if (opt == 'p')
		{
			if ((g_flags & (EXPORT_P | EXPORT_F | EXPORT_N)))
				return (ft_retf(WUT, N"%c : %e\n", EINVAL));
			g_flags |= EXPORT_P;
		}
		else
			return (WUT);
	return (g_optind);
}

inline int				sh_biexport(int ac, char **a, char **envv)
{
	char	*val;
	int		i;

	g_flags = 0;
	if ((i = exportparse(ac, a)) == ac || (i < 0))
		return (i == ac ? sh_vardump(envv) : EXIT_FAILURE);
	--i;
	while (++i < ac)
		if (*a[i] == '=')
			return (ft_retf(EXIT_FAILURE, N"%s: bad assignment\n", a[i]));
		else if ((val = ft_strchr(a[i], '=')))
			if (!sh_isident(a[i], val - a[i]))
				return (ft_retf(1, N"%s: not an identifier\n", a[i]));
			else
			{
				*val = '\0';
				export(a[i], ++val, envv);
			}
		else if (sh_isident(a[i], ft_strlen(a[i])))
			export(a[i], NULL, envv);
		else
			return (ft_retf(EXIT_FAILURE, N"%s: Invalid argument\n", a[i]));
	return (EXIT_SUCCESS);
}
