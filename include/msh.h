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
** [/] - librl (readline library)
** [/] - history (librl)
** [/] - autocomplete (librl)
** [/] - line edition (librl)
** [ ] - file stream adaptation to librl
** [ ] - lexing adaptation to librl
** [ ] - quote expansion adaptation to librl
** [ ] - heredoc adaptation to librl
** [ ] - fixes empty heredoc
** [ ] - proper syntax error
** [ ] - pipe fixes in some cases ? (see shell tester)
** [ ] - logical operators (BONUS)
** [ ] - async operator (BONUS)
** [ ] - variable expansion (BONUS)
** [ ] - subshell expansion (BONUS)
** [ ] - parenthesis (BONUS)
** [ ] - #! binary interpretation (BONUS)
** [ ] - &> redirection operator (BONUS)
*/

# include "msh/edit.h"
# include "msh/env.h"
# include "msh/hist.h"
# include "msh/job.h"
# include "msh/proc.h"
# include "msh/read.h"
# include "msh/screen.h"
# include "msh/shell.h"
# include "msh/lex.h"

#endif
