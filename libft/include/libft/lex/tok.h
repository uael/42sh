/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/tok.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_TOK_H
# define LIBFT_LEX_TOK_H

# include "loc.h"
# include "src.h"
# include "tokv.h"

union			u_tok
{
	uint32_t	id;
	t_tokv		*val;
};

typedef struct	s_tok
{
	uint16_t	lws;
	t_bool		is_is;
	union u_tok	id;
	t_loc		loc;
}				t_tok;

#endif
