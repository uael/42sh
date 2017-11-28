/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 14:38:40 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIB_H
# define LIBFT_LIB_H

# include <errno.h>
# include <stdlib.h>

# include "tys.h"
# include "cty.h"
# include "mem.h"

# define FT_INIT(S, TY) ft_memset(S, 0, sizeof(TY))

typedef int		t_st;
typedef ssize_t	t_sz;

# define OK (0)
# define NOK (1)
# define ERR(ERRNO) (-(ERRNO))
# define ENO ERR(errno)
# define ST_HDL(ST, OTHERWISE) ((ST) < 0 ? (ST) : (OTHERWISE))
# define ST_TOENO(ST) ERR(ST)
# define ISENO(ST, ERRNO) (ST_TOENO(ST) == (ERRNO))
# define ISE(S) ((S) < OK)
# define SZ_NOK(SZ) ((SZ) <= OK)
# define SZ_OK(SZ) ((SZ) > OK)
# define ST_NOK(ST) ((ST) != OK)
# define ST_OK(ST) ((ST) == OK)
# define SZ_TOST(SZ) (ISE(SZ) ? (t_st)(SZ) : (NOK))
# define ST_TOSZ(ST) (ISE(ST) ? (t_sz)(ST) : (OK))

# define ENIMPL (ELAST + 1)
# define EBOUND (ENIMPL + 1)

typedef void	(*t_dtor)(void *i, ...);

extern int64_t	ft_atoi(char const *str);
extern double	ft_atod(char const *str);
extern char		*ft_itoa(int64_t n, uint8_t base);
extern char		*ft_utoa(uint64_t n, uint8_t base);
extern int		ft_dtor(int code, t_dtor dtor, void *arg, char const *msg, ...);
extern int		ft_exit(int code, t_dtor dtor, void *arg, char const *msg, ...);
extern int		ft_ret(int code, char const *msg, ...);
extern int		ft_szret(int code, char const *msg, ...);
extern void		ft_pfree(void **pptr);
extern char		*ft_strerr(int errn);

#endif
