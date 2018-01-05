/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/io/fcntl.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 16:21:16 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_FCNTL_H
# define LIBFT_IO_FCNTL_H

# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>

# include "../buf.h"
# include "../ex.h"
# include "../int.h"
# include "../str.h"

# ifndef FT_PAGE_SIZE
#  if defined PAGE_SIZE && PAGE_SIZE <= 4096
#   define FT_PAGE_SIZE PAGE_SIZE
#  elif defined PAGESIZE && PAGESIZE <= 4096
#   define FT_PAGE_SIZE PAGESIZE
#  else
#   define FT_PAGE_SIZE 4096
#  endif
# endif

extern ssize_t	ft_read(int fd, void *buf, size_t sz);
extern ssize_t	ft_write(int fd, void const *buf, size_t sz);

#endif
