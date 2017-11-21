/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/src.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_SRC_H
# define LIBFT_LEX_SRC_H

# include "../io.h"
# include "loc.h"

typedef struct	s_src
{
	t_istream	in;
	t_loc		cur;
}				t_src;

extern void		ft_src_init_file(t_src *self, char const *filename);
extern void		ft_src_init_str(t_src *self, char const *str);
extern void		ft_src_init_nstr(t_src *self, char const *str, size_t n);
extern void		ft_src_dtor(t_src *self);
extern char		ft_src_peek(t_src *self, size_t n);
extern ssize_t	ft_src_get(t_src *self, char *buf, size_t n);
extern char		ft_src_next(t_src *self);

#endif
