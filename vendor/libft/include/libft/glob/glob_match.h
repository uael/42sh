/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:57:25 by mc                #+#    #+#             */
/*   Updated: 2018/02/09 21:07:13 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBUX_H
# define GLOBUX_H

# include "libft/tys.h" /* for t_bool */

/*
** Perform shell-style glob matching, returning true (1) if the match
** succeeds, or false (0) if it fails.
**
** @pat: Shell-style pattern to match, e.g. "*.[ch]".
** @str: String to match.  The pattern must match the entire string.
*/
t_bool glob_match(char const *pat, char const *str);

#endif /* GLOBUX_H */
