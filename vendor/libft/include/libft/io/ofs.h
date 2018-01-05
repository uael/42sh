/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/ofs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 16:21:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_OFS_H
# define LIBFT_IO_OFS_H

# include "fcntl.h"

typedef struct	s_ofs
{
	int			ofd;
	size_t		i;
	char		buf[FT_PAGE_SIZE + 1];
}				t_ofs;

extern void		ft_ofsctor(t_ofs *self, int ofd);
extern int		ft_ofsopen(t_ofs *self, char const *filename);
extern int		ft_ofsclose(t_ofs *self);
extern ssize_t	ft_ofsflush(t_ofs *self);
extern ssize_t	ft_ofswrc(t_ofs *self, unsigned char c);
extern ssize_t	ft_ofswr(t_ofs *self, void const *buf, size_t n);
extern ssize_t	ft_ofswrs(t_ofs *self, char const *buf);
extern ssize_t	ft_ofswrl(t_ofs *self, long i, uint8_t base);
extern ssize_t	ft_ofswrul(t_ofs *self, ulong i, uint8_t base);
extern ssize_t	ft_ofswrd(t_ofs *self, double i, int precision, uint8_t base);
extern ssize_t	ft_ofsvwrf(t_ofs *self, char const *f, va_list ap);
extern ssize_t	ft_ofswrf(t_ofs *self, char const *fmt, ...);

#endif
