/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:55:49 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 02:30:15 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Long ago, in UNIX V6, there was a program /etc/glob that would expand
** wildcard patterns. Soon afterward this became a shell built-in.
**
** These days there is also a library routine glob(3) that will
** perform this function for a user program.
**
** Now we are writing a clone of this. Things got a little weird, ok?
*/

#ifndef USH_GLOB_H
# define USH_GLOB_H

# include <stdlib.h>

/* # define DEBUG_MODE */
# ifdef DEBUG_MODE
#  include <stdio.h>
#  define CLR_BLACK "\033[30;01m"
#  define CLR_RED "\033[31;01m"
#  define CLR_GREEN "\033[32;01m"
#  define CLR_YELLOW "\033[33;01m"
#  define CLR_BLUE "\033[34;01m"
#  define CLR_MAGENTA "\033[35;01m"
#  define CLR_CYAN "\033[36;01m"
#  define CLR_WHITE "\033[37;01m"
#  define CLR_RESET "\033[0m"
#  define DEBUG_HEADER CLR_MAGENTA "[DEBUG] " CLR_RESET
#  define _DEBUG(str, ...) fprintf(stderr, DEBUG_HEADER str CLR_RESET "\n", ##__VA_ARGS__)
# else
#  define _DEBUG(str, ...) do {} while (0)
# endif

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

# define __GLOB_FLAGS	(GLOB_ERR | /* GLOB_MARK | */ GLOB_NOSORT |  GLOB_DOOFFS |  \
						 GLOB_NOESCAPE /* | GLOB_NOCHECK | GLOB_APPEND | */	\
						 /* GLOB_PERIOD | GLOB_ALTDIRFUNC | GLOB_BRACE | */	\
						 /* GLOB_NOMAGIC | GLOB_TILDE | GLOB_ONLYDIR | GLOB_TILDE_CHECK */)


/* Error returns from `globctor'.  */
#  define GLOB_NOSPACE 1	/* Ran out of memory.  */
#  define GLOB_ABORTED 2	/* Read error.  */
#  define GLOB_NOMATCH 3	/* No matches found.  */
#  define GLOB_NOSYS 4	/* Not implemented.  */
#  define GLOB_ABEND GLOB_ABORTED /* Compat */

# endif /* _GLOB_H */

# define GLOB_SUCCESS 0

/* Structure describing a globbing run.  */
typedef struct s_glob	t_glob;
struct					s_glob
{
	size_t	gl_pathc;    /* Count of paths matched so far  */
	char	**gl_pathv;  /* List of matched pathnames.  */
	size_t	gl_offs;     /* Slots to reserve in gl_pathv.  */
    int		gl_flags;    /* Set to FLAGS, maybe | GLOB_MAGCHAR.  */
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
