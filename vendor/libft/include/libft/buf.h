/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/buf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BUF_H
# define LIBFT_BUF_H

# include "str.h"
# include "math.h"

extern void		*ft_bufaver(void const *buf, size_t n, size_t len, size_t isz);
extern void		*ft_bufgrow(void const *buf, size_t n, size_t len, size_t isz);
extern void		*ft_bufpush(void const *buf, size_t n, size_t len, size_t isz);
extern size_t	ft_bufshift(void *buf, size_t len, size_t n, size_t isz);
extern void		*ft_bufat(void const *buf, size_t i, size_t isz);

#endif
