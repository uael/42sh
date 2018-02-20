/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 12:41:56 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_UTIL_H
# define GLOB_UTIL_H

# include <sys/types.h> /* for {open,read,close}dir */
# include <dirent.h> /* for {open,read,close}dir */

# include "libft/ft_glob.h" /* for t_glob and GLOBUX flags */
# include "libft/str.h" /* for ft_str* / ft_mem* */
# include "libft/sort.h" /* for ft_shellsort */
# include "libft/tys.h" /* for t_bool */

# ifndef PATH_MAX
#  ifdef OSX
#   include <sys/syslimits.h> /* for PATH_MAX */
#  endif
#  ifdef LINUX
#   include <linux/limits.h> /* for PATH_MAX */
#  endif
# endif

# ifndef TRUE
#  define TRUE				1
# endif
# ifndef FALSE
#  define FALSE				0
# endif

# define IS_DIR(dirent) ((dirent)->d_type == DT_DIR)

# define GLOBUX_BOOM_BABY 5
# define GLOBUX_NOBODY_GIVES_A_DAMN 6
/* # define GLOBUX_INITIALIZED (1 << 15) */

# define MAX_DEPTH			(1 << 8) //TODO


typedef unsigned char	t_byte;

/* Structure describing a glob match.  */
typedef struct s_match	t_match;
struct					s_match
{
	t_match	*next;
	t_byte	buf[sizeof(void *)];
};


/*
** in glob_is_magic.c:
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
char const	*is_magic(char const *pattern, int *flags);



/*
** in glob_list.c:
*/
t_match		*matchctor(char const *path, size_t len);
void		matchdtor(t_match *match);
void		add_match_to_list(t_match *match, t_match **match_list);
size_t		list_len(t_match *match_list);


/*
** in glob_dir.c:
*/
int			glob_count_depth(char const *pattern);
int			glob_open_dir(DIR **dir, char const *dir_name, int flags);
int			glob_close_dir(DIR *dir, int flags);
char const	*glob_get_sub_pattern(char const *pattern, int depth);
char const *glob_get_folder_name(char const *path);
int			glob_append_file_name(char *path_buf, char const *new_file, int flags);
int			glob_store_dir_name(char *path_buf, char const *prev_dir, \
								char const *new_dir);
#endif /* GLOB_UTIL_H */
