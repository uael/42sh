/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/12 20:23:16 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_CLIMB_TREE_H
# define GLOB_CLIMB_TREE_H

# include "libft/tys.h" /* for t_bool */
# include "libft/str.h" /* for ft_strchr */

# ifndef TRUE
#  define TRUE				1
# endif

# ifndef FALSE
#  define FALSE				0
# endif

# define MAX_DEPTH			4242 //TODO


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
t_bool glob_climb_tree(char const *pattern, int flags);

#endif /* GLOB_CLIMB_TREE_H */
