/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex/ft_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:27:49 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 12:56:41 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ex.h"

#include "libft/lib.h"
#include "libft/io.h"
#include "libft/fs.h"

static int		ex_dft_hdl(int rcode, void *arg)
{
	(void)arg;
	if (errno)
	{
		ft_putf(2, COLOR_BRED"error: "COLOR_RESET"%e\n", errno);
		exit(1);
	}
	return (rcode);
}

static t_ex_hdl	g_eno_hdls[FT_ELAST + 1] =
{
	[0] = {ex_dft_hdl, NULL}
};

inline t_ex_hdl	ft_exhdl(t_ex_cb cb, void *arg)
{
	return ((t_ex_hdl){cb, arg});
}

inline void		ft_exbind(int eno, t_ex_hdl hld, t_ex_hdl *out)
{
	if (eno < 0 || eno > FT_ELAST)
		return ;
	if (out && g_eno_hdls[eno].cb)
		ft_memcpy(out, &g_eno_hdls[eno], sizeof(t_ex_hdl));
	g_eno_hdls[eno] = hld;
}

inline void		ft_exunset(int eno)
{
	if (eno < 0 || eno > FT_ELAST)
		return ;
	ft_memset(g_eno_hdls + eno, 0, sizeof(t_ex_hdl));
}

inline t_ex_hdl	*ft_exget(int eno)
{
	if (eno < 0 || eno > FT_ELAST)
		return (NULL);
	return (g_eno_hdls[eno].cb ? &g_eno_hdls[eno] : g_eno_hdls);
}
