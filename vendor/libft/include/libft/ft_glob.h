/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 23:55:49 by mc                #+#    #+#             */
/*   Updated: 2018/03/05 22:27:35 by mc               ###   ########.fr       */
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

/*
** Bits set in the FLAGS argument to `globctor'.
** GLOBUX_ERR (1 << 0) // Return on read errors.
** GLOBUX_MARK (1 << 1) // Append a slash to each name.
** GLOBUX_NOSORT (1 << 2) // Don't sort the names.
** GLOBUX_DOOFFS (1 << 3) // Insert PGLOB->gl_offs NULLs.
** GLOBUX_NOCHECK (1 << 4) // If nothing matches, return the pattern.
** GLOBUX_APPEND (1 << 5) // Append to results of a previous call.
** GLOBUX_NOESCAPE (1 << 6) // Backslashes don't quote metacharacters.
** GLOBUX_PERIOD (1 << 7) // Leading `.' can be matched by metachars.
**
** GLOBUX_MAGCHAR (1 << 8) // Set in gl_flags if any metachars seen.
** GLOBUX_ALTDIRFUNC (1 << 9) // Use gl_opendir et al functions.
** GLOBUX_BRACE (1 << 10) // Expand "{a,b}" to "a" "b".
** GLOBUX_NOMAGIC (1 << 11) // If no magic chars, return the pattern.
** GLOBUX_TILDE (1 << 12) // Expand ~user and ~ to home directories.
** GLOBUX_ONLYDIR (1 << 13) // Match only directories.
** GLOBUX_TILDE_CHECK (1 << 14) // Like GLOBUX_TILDE but return an err
**										if the user name is not available.
*/
# define GLOBUX_ERR (1 << 0)
# define GLOBUX_MARK (1 << 1)
# define GLOBUX_NOSORT (1 << 2)
# define GLOBUX_DOOFFS (1 << 3)
# define GLOBUX_NOCHECK (1 << 4)
# define GLOBUX_APPEND (1 << 5)
# define GLOBUX_NOESCAPE (1 << 6)
# define GLOBUX_PERIOD (1 << 7)

# define GLOBUX_MAGCHAR (1 << 8)
# define GLOBUX_NOMATCH_FLAG (1 << 9)
# define GLOBUX_BRACE (1 << 10)
# define GLOBUX_NOMAGIC (1 << 11)
# define GLOBUX_TILDE (1 << 12)
# define GLOBUX_ONLYDIR (1 << 13)
# define GLOBUX_TILDE_CHECK (1 << 14)

/*
** Not implemented: (handled in ush)
** GLOBUX_TILDE | GLOBUX_TILDE_CHECK
*/
# define FLAGS_A (GLOBUX_ERR | GLOBUX_MARK | GLOBUX_NOSORT | GLOBUX_ONLYDIR)
# define FLAGS_B (GLOBUX_DOOFFS | GLOBUX_NOESCAPE | GLOBUX_NOCHECK)
# define FLAGS_C (GLOBUX_PERIOD | GLOBUX_BRACE | GLOBUX_NOMAGIC | GLOBUX_APPEND)
# define __GLOBUX_FLAGS	(FLAGS_A | FLAGS_B | FLAGS_C | GLOBUX_NOMATCH_FLAG)

/*
** Error returns from `globctor'.
**
** GLOBUX_SUCCESS 0 // Yay
** GLOBUX_NOSPACE 1   // Ran out of memory.
** GLOBUX_ABORTED 2   // Read error.
** GLOBUX_NOMATCH 3   // No matches found.
** GLOBUX_NOSYS 4 // Not implemented.
** GLOBUX_ABEND GLOBUX_ABORTED // Compat
*/
# define GLOBUX_SUCCESS 0
# define GLOBUX_NOSPACE 1
# define GLOBUX_ABORTED 2
# define GLOBUX_NOMATCH 3
# define GLOBUX_NOSYS 4
# define GLOBUX_ABEND GLOBUX_ABORTED

/*
** Structure describing a globbing run.
**
** typedef struct s_glob	t_glob;
** struct					s_glob
** {
** 	size_t	gl_pathc;    // Count of paths matched so far
** 	char	**gl_pathv;  // List of matched pathnames.
** 	size_t	gl_offs;     // Slots to reserve in gl_pathv.
**  int		gl_flags;    // Set to FLAGS, maybe | GLOBUX_MAGCHAR.
**  int     gl_padding;  // Just for struct padding
** };
*/
typedef struct s_glob	t_glob;
struct					s_glob
{
	size_t	gl_pathc;
	char	**gl_pathv;
	size_t	gl_offs;
	int		gl_flags;
	int		gl_padding;
};

/*
** The ft_glob() function searches for all the pathnames matching pattern
** according to the rules used by the shell (see glob(7)).
** No tilde expansion or parameter substitution is done;
** if you want these, use wordexp(3).
*/
int						ft_glob(const char *pattern, int flags, t_glob *pglob);

/*
** The ft_globfree() function frees the dynamically allocated storage from an
** earlier call to ft_glob().
*/
void					ft_globfree(t_glob *pglob);

#endif
