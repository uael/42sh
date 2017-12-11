/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 15:54:12 by alucas-          ###   ########.fr       */
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

# define YEP (0)
# define NOP (1)
# define WUT (-1)
# define TRUE (1)
# define FALSE (0)

# ifndef ELAST
#  define ELAST 200
# endif

# define ENIMPL (ELAST + 1)
# define EBOUND (ENIMPL + 1)
# define FT_ELAST (EBOUND)

typedef void	(*t_dtor)(void *i, ...);
typedef int		(*t_err_hdl)(void *self, int code);

extern int64_t	ft_atoi(char const *str);
extern double	ft_atod(char const *str);
extern char		*ft_itoa(int64_t n, uint8_t base);
extern char		*ft_utoa(uint64_t n, uint8_t base);

extern char		*ft_strerr(int errn);
extern int		ft_dtor(int no, t_dtor dtor, void *arg, char const *msg, ...);
extern int		ft_fatal(int no, t_dtor dtor, void *arg, char const *msg, ...);
extern int		ft_retf(int no, char const *msg, ...);
extern int		ft_szret(int no, char const *msg, ...);

extern void		ft_pfree(void **pptr);
extern void		ft_clean(void *ptr);

extern char		*ft_join(char const *s1, char const *s2, char n);
extern char		*ft_getenv(char **env, char *var);
extern t_st		ft_setenv(char **env, char *var, char *val);

# define GC(T) __attribute__((__cleanup__(ft_clean))) T

#endif
