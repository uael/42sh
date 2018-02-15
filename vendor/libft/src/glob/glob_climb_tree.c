/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:23:43 by mc                #+#    #+#             */
/*   Updated: 2018/02/15 22:46:19 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** glob_climb_tree - glob util function to check recursively a directory tree
*/

#include "glob_climb_tree.h"

char *g_dirname_buf; //TODO: don't

/*
static char **handle_brace_expansion(char const *pattern)
{
	//TODO
	(void)pattern;

	return (char **)42;
}
*/

static int	glob_check_file(struct dirent *dirent, char const *pattern, \
							 int flags, t_match **match_list, int depth) //TODO: ooops
{
	int			ret;
	t_match		*match;

	if ((flags & GLOBUX_ONLYDIR) && !IS_DIR(dirent))
		return GLOBUX_SUCCESS;

	if (!glob_match(pattern, dirent->d_name, flags))
		return GLOBUX_SUCCESS;

	if ((flags & GLOBUX_PERIOD) && !(flags & GLOBUX_MAGCHAR) \
			&& *(dirent->d_name) == '.')
		return GLOBUX_SUCCESS;

	if (!(match = matchctor(dirent->d_name, dirent->d_reclen)))
		return GLOBUX_NOSPACE;
	add_match_to_list(match, match_list);

	if (IS_DIR(dirent)) //TODO: not '.' and '..'
	{
		//TODO: the recursion fuck up g_dirname_buf
		//TODO: ps: this buffer is way too small anyway
		ret = glob_read_dir(pattern, flags, match_list, depth - 1); //BOOOOM BABY!
		if (ret != GLOBUX_SUCCESS)
			return ret;
	}

	return GLOBUX_SUCCESS;
}

int			glob_read_dir(char const *pattern, int flags, \
						  t_match **match_list, int depth)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				ret;

	if (!depth)
		return GLOBUX_SUCCESS;

	if (!*g_dirname_buf)
		*g_dirname_buf = *pattern == '/' ? '/' : '.';
	else if (glob_append_dir_name(pattern) != GLOBUX_SUCCESS)
		return GLOBUX_NOSPACE;

	ret = glob_open_dir(&dir, flags);
	if (ret != GLOBUX_SUCCESS)
		return ret;

	while ((dirent = readdir(dir)))
	{
		ret = glob_check_file(dirent, pattern, flags, match_list, depth);
		if (ret != GLOBUX_SUCCESS)
		{
			glob_close_dir(dir, flags);
			return ret;
		}
	}
/*
	//TODO: errno
	if (read_error && (flags & GLOBUX_ERR))
		return GLOBUX_ABORTED;
*/

	return glob_close_dir(dir, flags);
}

int			glob_climb_tree(char const *pattern, t_glob *pglob, t_match **match_list)
{
/*
	handle_flags(GLOBUX_TILDE | GLOBUX_TILDE_CHECK)

	if '{' in pattern and GLOBUX_BRACE:
		patterns[] = handle_brace_expansion(pattern)
			for pat in patterns:
				if not glob_climb_tree(patn flags)
					return false;
*/
	int			depth;
	int			ret;
	char		hopefully_this_variable_wont_used_too_much[DIRNAME_BUF_SIZE];

	g_dirname_buf = hopefully_this_variable_wont_used_too_much;
	ft_bzero(g_dirname_buf, DIRNAME_BUF_SIZE);

	depth = glob_count_depth(pattern);
	if (depth > MAX_DEPTH)
		return GLOBUX_NOSPACE;

	/* DEBUG */
	char const	*magic;

	if ((magic = is_magic(pattern, pglob->gl_flags)))
	{
		pglob->gl_flags |= GLOBUX_MAGCHAR;
		//TODO: open(magic);
		//TODO: glob_read_dir(?, pglob->gl_flags, match_list, depth)
	}
	else if ((pglob->gl_flags & GLOBUX_NOMAGIC))
	{
		if (!(*match_list = matchctor(pattern, ft_strlen(pattern))))
			return GLOBUX_NOSPACE;
		return GLOBUX_SUCCESS;
	}
	/* DEBUG */

	//TODO: pass t_glob (you'll need ac too)
	ret = glob_read_dir(pattern, pglob->gl_flags, match_list, depth);

	return ret;
}
