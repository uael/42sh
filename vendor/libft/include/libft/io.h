/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:01:44 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include <unistd.h>
# include <fcntl.h>

# include "int.h"
# include "str.h"

# include "io/ifs.h"
# include "io/ofs.h"
# include "io/imstream.h"
# include "io/istream.h"
# include "io/ofstream.h"
# include "io/omstream.h"
# include "io/ostream.h"
# include "io/fcntl.h"

extern ssize_t	ft_putc(int fd, char c);
extern ssize_t	ft_putl(int fd, char const *s);
extern ssize_t	ft_putd(int fd, float n, int precision, uint8_t base);
extern ssize_t	ft_putn(int fd, int64_t n, uint8_t base);
extern ssize_t	ft_putu(int fd, uint64_t n, uint8_t base);
extern ssize_t	ft_padnl(int fd, int64_t n, uint8_t base, size_t pad);
extern ssize_t	ft_padnr(int fd, int64_t n, uint8_t base, size_t pad);
extern ssize_t	ft_padul(int fd, uint64_t n, uint8_t base, size_t pad);
extern ssize_t	ft_padur(int fd, uint64_t n, uint8_t base, size_t pad);
extern ssize_t	ft_puts(int fd, char const *s);
extern ssize_t	ft_putr(int fd, char c, size_t n);
extern ssize_t	ft_padl(int fd, char const *s, size_t pad);
extern ssize_t	ft_padr(int fd, char const *s, size_t pad);
extern ssize_t	ft_putf(int fd, char const *fmt, ...);
extern ssize_t	ft_vputf(int fd, char const *f, va_list ap);

#endif
