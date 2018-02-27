/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIB_H
# define LIBFT_LIB_H

# include <errno.h>
# include <stdlib.h>

# include "tys.h"
# include "cty.h"
# include "mem.h"

# define YEP (0)
# define NOP (1)
# define OUF (2)
# define WUT (-1)

# ifndef ELAST
#  define ELAST 200
# endif

# define ENIMPL (ELAST + 1)
# define EBOUND (ENIMPL + 1)
# define ENOTRM (EBOUND + 1)
# define ENOARG (ENOTRM + 1)
# define FT_ELAST (ENOARG)

struct s_vec;

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

extern int		ft_pfree(void **pptr);
extern void		ft_clean(void *ptr);

extern char		*ft_join(char const *s1, char const *s2, char n);
extern char		*ft_getenv(char **env, char const *var);
extern void		ft_setenv(struct s_vec *env, char *var, char *val);
extern t_bool	ft_unsetenv(struct s_vec *env, char *var, t_bool delm);

#endif
