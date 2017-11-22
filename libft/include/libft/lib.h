/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/17 10:03:31 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIB_H
# define LIBFT_LIB_H

# include <stdlib.h>

# include "tys.h"
# include "cty.h"
# include "mem.h"

# define FT_INIT(S, TY) ft_memset(S, 0, sizeof(TY))

typedef enum	e_ret
{
	RET_ERR = -1,
	RET_OK = 0,
	RET_NOK = 1
}				t_ret;

typedef void	(*t_dtor)(void *i);

extern int64_t	ft_atoi(char const *str);
extern double	ft_atod(char const *str);
extern char		*ft_itoa(int64_t n, uint8_t base);
extern char		*ft_utoa(uint64_t n, uint8_t base);
extern t_ret	ft_dtor(t_ret code, t_dtor dtor, void *arg);

#endif
