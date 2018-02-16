/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/15 13:41:14 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_MATCH_H
# define GLOB_MATCH_H

# include "libft/tys.h" /* for t_bool */

# ifndef TRUE
#  define TRUE				1
# endif

# ifndef FALSE
#  define FALSE				0
# endif

# define MAX_DEPTH			(1 << 8) //TODO


/*
** Perform shell-style glob matching, returning true (1) if the match
** succeeds, or false (0) if it fails.
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
** @str: String to match.  The pattern must match the entire string.
** @flags: cf ft_glob.h (GLOBUX_NOESCAPE | GLOBUX_PERIOD | GLOBUX_BRACE)
*/
t_bool		glob_match(char const *pat, char const *str, int flags);


/*
** in glob_list.c:
**
** Check if a pattern contains any magic char, otherwise return NULL.
** If a magic char is found, a pointer to the last non-magic (muggle?)
** directory is returned.
**
** This function is actually here to avoid calling glob_match() too much
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
** @flags: cf ft_glob.h (GLOBUX_NOESCAPE)
*/
char const	*is_magic(char const *pattern, int flags);

#endif /* GLOB_MATCH_H */
