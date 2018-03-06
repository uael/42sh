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

#ifndef USH_BI_H
# define USH_BI_H

# include <libps.h>

enum			e_opt
{
	HISTORY_C = 1 << 1,
	HISTORY_D = 1 << 2,
	HISTORY_W = 1 << 3,
	HISTORY_A = 1 << 4,
	HISTORY_R = 1 << 5,
	HISTORY_P = 1 << 6,
	HISTORY_S = 1 << 7
};

typedef	struct	s_histopt
{
	uint8_t	flags;
	uint8_t	offset;
	char	*filename;
	char	*arg;
}				t_histopt;

typedef struct	s_readopt
{
	ssize_t		timeout;
	char		delim;
	int			fd;
	char		*prompt;
	uint8_t		flags;
	int			nchars;
}				t_readopt;

extern void		sh_biregister(void);
extern int		sh_bialias(int ac, char **av);
extern int		sh_biecho(int ac, char **argv, char **env);
extern int		sh_biexit(int ac, char **av, char **env);
extern int		sh_biunsetenv(int ac, char **av, char **env);
extern int		sh_bienv(int ac, char **av, char **env);
extern int		sh_bisetenv(int ac, char **av, char **env);
extern int		sh_bicd(int ac, char **av, char **env);
extern int		sh_biunset(int ac, char **av);
extern int		sh_biexport(int ac, char **av, char **env);
extern int		sh_bihistory(int ac, char **av, char **env);
extern int		sh_biread(int ac, char **av, char **env);

#endif
