/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh/env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include "sh.h"

extern t_ret	msh_initenv(t_msh *self, char **env);
extern char		**msh_getenv(t_msh *self, char *var);
extern t_ret	msh_setenv(t_msh *self, char *var, char *val);
extern t_ret	msh_envadd(t_msh *self, char *var, char *val);
extern t_ret	msh_unsetenv(t_msh *self, char *var);

#endif
