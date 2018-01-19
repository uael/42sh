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
	char	*s;
	int		has_arg;
	int		*f;
	int		val;
}               t_opt;

/*
 ** name is the name of the long option
 ** has_arg = 0 if options takes no arguments, = 1 if one argument, = 2 if one optional argument
 ** if flag == NULL, get_opt_long() return val, else get_opt_long = 0 and flag is pointing to a variable corresponding to val if an option has been found
 ** val is the value to return or the load in the variable pointed by flag 
*/

extern int		g_optind;
extern char		*g_optarg;
extern int		g_opterr;

/*
 ** optind is the index where the analysis is
 ** optstring is a string containing all of the existant options
 ** optarg is defined to zero exept if one option has ":" behind it which would means that it requieres another option it becomes a pointer to the first element of the new option
 ** if opterr = 0 no error message will be prompt, else a prompt message will appear
 ** optopt is the option find
*/

int			ft_getopt_long(int ac, char **av,
						char *optstring, t_opt *longopt);
int			ft_getopt_long_long(t_opt *lopt, char **av, char *pname);
void		ft_getopt_init(char **pname, char **nextchar, char *s);
int		ft_getopt(int ac, const char **av, const char *optstring);

#endif