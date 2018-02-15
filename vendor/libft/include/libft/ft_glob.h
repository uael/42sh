/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:55:49 by mc                #+#    #+#             */
/*   Updated: 2018/02/15 13:02:24 by mc               ###   ########.fr       */
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

#ifndef FT_GLOB_H
# define FT_GLOB_H

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

/* Bits set in the FLAGS argument to `globctor'.  */
# define GLOBUX_ERR (1 << 0) /* Return on read errors.  */
# define GLOBUX_MARK (1 << 1) /* Append a slash to each name.  */
# define GLOBUX_NOSORT (1 << 2) /* Don't sort the names.  */
# define GLOBUX_DOOFFS (1 << 3) /* Insert PGLOB->gl_offs NULLs.  */
# define GLOBUX_NOCHECK (1 << 4) /* If nothing matches, return the pattern.  */
# define GLOBUX_APPEND (1 << 5) /* Append to results of a previous call.  */
# define GLOBUX_NOESCAPE (1 << 6) /* Backslashes don't quote metacharacters.  */
# define GLOBUX_PERIOD (1 << 7) /* Leading `.' can be matched by metachars.  */

# define GLOBUX_MAGCHAR (1 << 8) /* Set in gl_flags if any metachars seen.  */
# define GLOBUX_ALTDIRFUNC (1 << 9) /* Use gl_opendir et al functions.  */
# define GLOBUX_BRACE (1 << 10) /* Expand "{a,b}" to "a" "b".  */
# define GLOBUX_NOMAGIC (1 << 11) /* If no magic chars, return the pattern.  */
# define GLOBUX_TILDE (1 << 12) /* Expand ~user and ~ to home directories. */
# define GLOBUX_ONLYDIR (1 << 13) /* Match only directories.  */
# define GLOBUX_TILDE_CHECK (1 << 14) /* Like GLOBUX_TILDE but return an error
										if the user name is not available.  */

# define __GLOBUX_FLAGS	(GLOBUX_ERR | /* GLOBUX_MARK | */ GLOBUX_NOSORT |  GLOBUX_DOOFFS |  \
						 GLOBUX_NOESCAPE /* | GLOBUX_NOCHECK | GLOBUX_APPEND | */	\
						 /* GLOBUX_PERIOD | GLOBUX_ALTDIRFUNC | GLOBUX_BRACE | */	\
						 /* GLOBUX_NOMAGIC | GLOBUX_TILDE */ | GLOBUX_ONLYDIR /* | GLOBUX_TILDE_CHECK */)


/* Error returns from `globctor'.  */
# define GLOBUX_SUCCESS 0 /* Yay */
# define GLOBUX_NOSPACE 1	/* Ran out of memory.  */
# define GLOBUX_ABORTED 2	/* Read error.  */
# define GLOBUX_NOMATCH 3	/* No matches found.  */
# define GLOBUX_NOSYS 4	/* Not implemented.  */
# define GLOBUX_ABEND GLOBUX_ABORTED /* Compat */


/* Structure describing a globbing run.  */
typedef struct s_glob	t_glob;
struct					s_glob
{
	size_t	gl_pathc;    /* Count of paths matched so far  */
	char	**gl_pathv;  /* List of matched pathnames.  */
	size_t	gl_offs;     /* Slots to reserve in gl_pathv.  */
    int		gl_flags;    /* Set to FLAGS, maybe | GLOBUX_MAGCHAR.  */
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

#endif /* FT_GLOB_H */
