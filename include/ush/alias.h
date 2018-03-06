/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/alias.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_ALIAS_H
# define USH_ALIAS_H

# include <libft.h>

extern void		sh_aliasdtor(void);
extern int		sh_aliasdump(void);
extern void		sh_aliasset(char const *alias, char const *val);
extern char		*sh_aliasget(char const *alias);

#endif
