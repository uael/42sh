/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/private.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 06:56:48 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_PRIVATE_H
# define LIBFT_LEX_PRIVATE_H

# include "libft/lex/src.h"

extern ssize_t	ft_src_next(t_src *self, char *peek, size_t n);
extern int		ft_src_peek(t_src *self, char *c, size_t n);

#endif
