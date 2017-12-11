/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/ex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:45:54 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 12:56:41 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EX_H
# define LIBFT_EX_H

typedef int		(*t_ex_cb)(int rcode, void *arg);

typedef struct	s_ex_hdl
{
	t_ex_cb		cb;
	void		*arg;
}				t_ex_hdl;

extern t_ex_hdl	ft_ex_hdl(t_ex_cb cb, void *arg);
extern void		ft_ex_register(int eno, t_ex_hdl hld, t_ex_hdl *out);
extern void		ft_ex_unregister(int eno);
extern t_ex_hdl	*ft_ex_get(int eno);
extern int		ft_ex_throw(int rcode);
extern int		ft_eno_throw(int rcode, int eno);

#endif
