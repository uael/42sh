/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/22 16:43:27 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_MATCH_H
# define GLOB_MATCH_H

# include "glob_util/glob_util.h"

/*
** Perform shell-style glob matching, returning true (1) if the match
** succeeds, or false (0) if it fails.
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
** @str: String to match.	The pattern must match the entire string.
** @flags: cf ft_glob.h (GLOBUX_NOESCAPE | GLOBUX_PERIOD | GLOBUX_BRACE)
*/
int		glob_match(char const *pat, char const *str, int flags);

#endif
