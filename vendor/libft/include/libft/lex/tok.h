/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tok.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/22 10:29:53 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_TOK_H
# define LIBFT_LEX_TOK_H

# include "loc.h"
# include "src.h"
# include "tokv.h"

typedef struct	s_tok
{
	uint8_t		id;
	t_loc		loc;
	t_tokv		*val;
}				t_tok;

extern void		ft_tok_dtor(t_tok *self);
extern t_dstr	*ft_tok_str(t_tok *self);
extern t_dstr	*ft_tok_ident(t_tok *self);

#endif
