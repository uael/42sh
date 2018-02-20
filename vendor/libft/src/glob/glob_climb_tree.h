/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_climb_tree.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 13:37:55 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_CLIMB_TREE_H
# define GLOB_CLIMB_TREE_H

# include "glob_match.h" /* for glob_match */
# include "glob_util/glob_util.h" /* for glob_* */


/* Structure describing a glob tree climbing environment.  */
typedef struct s_glob_env	t_glob_env;
struct                      s_glob_env
{
    t_match     *match_list;
    char const  *pattern; //TODO: copy to a(nother) buf instead
    char        sub_pat_buf[NAME_MAX + 1];
    char        magic_buf[NAME_MAX + 1];
    int         *flags;
};


/*
** Recursively check PAT on the matching directory tree
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
*/
int			glob_climb_tree(t_glob_env *glob_env);


/*
** TODO: doc
*/
int			glob_read_dir(t_glob_env *glob_env, \
                          int depth, char const *dir_name);

#endif /* GLOB_CLIMB_TREE_H */
