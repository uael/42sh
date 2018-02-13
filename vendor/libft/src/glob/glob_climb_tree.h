/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 02:09:35 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_CLIMB_TREE_H
# define GLOB_CLIMB_TREE_H

# include "libft/str.h" /* for ft_strchr */
# include "libft/zob.h" /* for ft_shellsort */
# include "glob_match.h" /* for glob_match */


/* Structure describing a glob match.  */
typedef struct s_match	t_match;
struct					s_match
{
	t_match	*next;
	char	buf[1];
};


/*
** Recursively check PAT on the matching directory tree
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
*/
int		glob_climb_tree(char const *pattern, int flags, t_match **match_list);

#endif /* GLOB_CLIMB_TREE_H */
