/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/24 12:48:51 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_CLIMB_TREE_H
# define GLOB_CLIMB_TREE_H

# include "glob_match.h"
# include "glob_util/glob_util.h"

/*
** Recursively check PAT on the matching directory tree
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
*/
int							glob_climb_tree(t_glob_env *glob_env);

/*
** TODO: doc
*/
int							glob_read_dir(t_glob_env *glob_env, \
							int depth, char const *dir_name);

/*
** in glob_brace.c
*/
int							glob_brace(t_glob_env *e);

#endif
