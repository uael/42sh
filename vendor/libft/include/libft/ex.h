/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:45:54 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/12 12:38:54 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EX_H
# define LIBFT_EX_H

# ifdef DEBUG
#  define FT_FUNC __FUNCTION__
#  define FT_LINE __LINE__
# else
#  define FT_FUNC NULL
#  define FT_LINE 0
# endif
# define FT_DBG FT_FUNC,FT_LINE

# define EXALL 0

typedef int		(*t_ex_cb)(int rcode, void *arg);

typedef struct	s_ex_hdl
{
	t_ex_cb		cb;
	void		*arg;
}				t_ex_hdl;

extern t_ex_hdl	ft_exhdl(t_ex_cb cb, void *arg);
extern void		ft_exbind(int eno, t_ex_hdl hld, t_ex_hdl *out);
extern void		ft_exunset(int eno);
extern t_ex_hdl	*ft_exget(int eno);
extern int		ft_throw(int rcode, char const *fn, int line);
extern int		ft_ethrow(int rcode, int eno, char const *msg, int line);

#endif
