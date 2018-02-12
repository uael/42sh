/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/ifs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 16:21:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_IFS_H
# define LIBFT_IO_IFS_H

# include "fcntl.h"

typedef struct	s_ifs
{
	int			ifd;
	size_t		i;
	size_t		rd;
	size_t		limit;
	char		*buf;
	char		stack[FT_PAGE_SIZE + 1];
}				t_ifs;

extern void		ft_ifsctor(t_ifs *self, int ifd);
extern void		ft_ifsdtor(t_ifs *self);
extern int		ft_ifsopen(t_ifs *self, char const *filename);
extern int		ft_ifsclose(t_ifs *self);
extern char		ft_ifspeek(t_ifs *self, size_t i);
extern ssize_t	ft_ifsbuf(t_ifs *self, size_t sz, char **out);
extern ssize_t	ft_ifschr(t_ifs *self, size_t off, char c, char **out);
extern ssize_t	ft_ifsrd(t_ifs *s, void *b, size_t n);

#endif
