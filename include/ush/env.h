/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_ENV_H
# define USH_ENV_H

# include <libft.h>

extern char		**g_env;

extern void		sh_envdtor(void);
extern void		sh_envinit(char **envv);
extern char		*sh_getenv(char *var);
extern void		sh_setenv(char *var, char *val);
t_bool			sh_unsetenv(char *var, t_bool m);

#endif
