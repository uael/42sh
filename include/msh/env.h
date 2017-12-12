/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:25:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include "sh.h"

extern void		sh_initenv(t_vstr *self, char **env);
extern void		sh_setenv(t_vstr *self, char *var, char *val);
extern t_bool	sh_envadd(t_vstr *self, char *var, char *val);
extern t_bool	sh_unsetenv(t_vstr *self, char *var, t_bool m);

#endif
