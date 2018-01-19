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

#include "ush/bi.h"

#define ENV_I (1 << 0)
#define ENV_P (0)
#define ENV_U (1)
#define M_DUP "Duplicate option"
#define N_ENV COLOR_RED COLOR_BOLD "env: " COLOR_RESET

inline int	sh_bienv(int ac, char **av, char **env)
{
	int i;

	(void)ac;
	(void)av;
	(void)env;
	i = -1;
	while (env[++i])
		ft_putf(1, "%s\n", env[i]);
	return (EXIT_SUCCESS);
}

