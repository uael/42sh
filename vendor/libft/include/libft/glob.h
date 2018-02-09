/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:55:49 by mc                #+#    #+#             */
/*   Updated: 2018/02/09 20:59:00 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_GLOB_H
# define USH_GLOB_H

# include <stdlib.h>

# ifndef _GLOB_H

/* Bits set in the FLAGS argument to `globctor'.  */
#  define GLOB_ERR (1 << 0) /* Return on read errors.  */
#  define GLOB_MARK (1 << 1) /* Append a slash to each name.  */
#  define GLOB_NOSORT (1 << 2) /* Don't sort the names.  */
#  define GLOB_DOOFFS (1 << 3) /* Insert PGLOB->gl_offs NULLs.  */
#  define GLOB_NOCHECK (1 << 4) /* If nothing matches, return the pattern.  */
#  define GLOB_APPEND (1 << 5) /* Append to results of a previous call.  */
#  define GLOB_NOESCAPE (1 << 6) /* Backslashes don't quote metacharacters.  */
#  define GLOB_PERIOD (1 << 7) /* Leading `.' can be matched by metachars.  */

#  define GLOB_MAGCHAR (1 << 8) /* Set in gl_flags if any metachars seen.  */
#  define GLOB_ALTDIRFUNC (1 << 9) /* Use gl_opendir et al functions.  */
#  define GLOB_BRACE (1 << 10) /* Expand "{a,b}" to "a" "b".  */
#  define GLOB_NOMAGIC (1 << 11) /* If no magic chars, return the pattern.  */
#  define GLOB_TILDE (1 << 12) /* Expand ~user and ~ to home directories. */
#  define GLOB_ONLYDIR (1 << 13) /* Match only directories.  */
#  define GLOB_TILDE_CHECK (1 << 14) /* Like GLOB_TILDE but return an error
										if the user name is not available.  */
/* Error returns from `globctor'.  */
#  define GLOB_NOSPACE 1	/* Ran out of memory.  */
#  define GLOB_ABORTED 2	/* Read error.  */
#  define GLOB_NOMATCH 3	/* No matches found.  */
#  define GLOB_NOSYS 4	/* Not implemented.  */
#  define GLOB_ABEND GLOB_ABORTED /* Compat */

# endif /* _GLOB_H */

/* Structure describing a globbing run.  */
typedef struct s_glob	t_glob;
struct					s_glob
{
	size_t   gl_pathc;    /* Count of paths matched so far  */
	char   **gl_pathv;    /* List of matched pathnames.  */
	size_t   gl_offs;     /* Slots to reserve in gl_pathv.  */
};

/*
** The globctor() function searches for all the pathnames matching pattern
** according to the rules used by the shell (see glob(7)).
** No tilde expansion or parameter substitution is done;
** if you want these, use wordexp(3).
*/
int		globctor(const char *pattern, int flags, t_glob *pglob);

/*
** The globdtor() function frees the dynamically allocated storage from an
** earlier call to globctor().
*/
void	globdtor(t_glob *pglob);

#endif /* USH_GLOB_H */
