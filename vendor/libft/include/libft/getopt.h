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

#ifndef LIBFT_GETOPT_H
# define LIBFT_GETOPT_H

# include "str.h"
# include "io.h"

# define OPT_ISOPT(opt) ((opt)[0] == '-' && (opt)[1])
# define OPT_ISLONG(opt) (!ft_strncmp((opt), "--", 2) && (opt)[2] != 0)
# define OPT_ISEND(opt) (!ft_strcmp((opt), "--"))

enum			e_arg
{
	no_arg,
	req_arg,
	opt_arg
};

typedef struct	s_opt
{
	char		*s;
	int			has_arg;
	int			*f;
	int			val;
}				t_opt;

extern int		g_optind;
extern char		*g_optarg;
extern int		g_opterr;

int				ft_lgetopt(int ac, char **av, char *optstring, t_opt *longopt);
int				ft_llgetopt(t_opt *lopt, char **av, char *pname);
void			ft_getopt_init(char **pname, char **nextchar, char *s);
int				ft_getopt(int ac, const char **av, const char *optstring);

#endif
