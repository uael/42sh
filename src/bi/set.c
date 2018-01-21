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

inline int	sh_biset(int argc, char **argv, char **env)
{
	(void)env;
	if (argc == 1)
	{
		sh_vardump();
		return (YEP);
	}
	else if (argc == 2 || argc == 3)
	{
		if (ft_strchr(argv[1], '='))
		{
			ft_putf(STDERR_FILENO, "It's forbidden to use '='\n");
			return (NOP);
		}
		sh_varset(argv[1], argv[2]);
		return (YEP);
	}
	else
		ft_putf(STDERR_FILENO, "Usage: set <key> <value>\n");
	return (NOP);
}
