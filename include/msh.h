/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

/*
** TODO
** [X] - builtin cd
** [X] - builtin env
** [X] - builtin setenv/export
** [X] - builtin unsetenv
** [X] - builtin echo
** [X] - builtin exit
** [X] - basic command
** [X] - semicolon separator
** [X] - shell script
** [X] - pipe
** [X] - redirection
** [X] - redirection fd duplication
** [X] - exit status
** [ ] - proper syntax error
** [ ] - history
** [ ] - autocomplete
** [ ] - line edition
** [ ] - logical operator
** [ ] - variable expansion
** [ ] - subshell expansion
** [ ] - parenthesis
*/

# include "msh/env.h"
# include "msh/eval.h"
# include "msh/history.h"
# include "msh/lex.h"
# include "msh/reduce.h"
# include "msh/sh.h"
# include "msh/sig.h"

#endif
