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

extern t_st	sh_initenv(t_sh *self, char **env);
extern char	**sh_getenv(t_sh *self, char *var);
extern t_st	sh_setenv(t_sh *self, char *var, char *val);
extern t_st	sh_envadd(t_sh *self, char *var, char *val);
extern t_st	sh_unsetenv(t_sh *self, char *var);

#endif
