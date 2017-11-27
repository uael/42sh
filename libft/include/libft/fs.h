/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/fs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 10:01:04 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FS_H
# define LIBFT_FS_H

# include "io.h"

extern char	const	*ft_basename(char const *path);
extern t_bool		ft_isdots(char const *path);
extern char			*ft_pathjoin(char const *p1, char const *p2);
extern char			*ft_pathresolve(char const *p);
extern char			*ft_pathcat(char *dst, char const *src);

#endif
