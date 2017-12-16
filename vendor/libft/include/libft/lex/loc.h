/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lex/loc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LEX_LOC_H
# define LIBFT_LEX_LOC_H

# include "../tys.h"

struct s_src;

typedef struct	s_loc
{
	struct s_src	*src;
	uint16_t		line;
	uint16_t		col;
	uint32_t		cur;
	uint16_t		len;
}				t_loc;

#endif
