/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read/notty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:11:59 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>

#include "../read.h"

#ifndef OPEN_MAX
# define OPEN_MAX RLIMIT_NOFILE
#endif

static t_ifs	g_in[OPEN_MAX + 1] = { { 0, 0, 0, -1, 1, 0, { 0 } } };
static t_sds	g_ln = { NULL, 0, 0 };
static ssize_t	g_rd[OPEN_MAX + 1] = { 0 };

inline void				rl_nottydtor(void)
{
	ft_sdsdtor(&g_ln);
}

inline void				rl_nottyfinalize(int fd)
{
	if (g_in[fd].ifd > 0)
		ft_ifsclose(g_in + fd);
}

inline int				rl_readnotty(int fd, char **ln)
{
	char *buf;

	if (fd < 0 || fd > OPEN_MAX)
		return (ft_ethrow(WUT, EINVAL, FT_DBG));
	g_in[fd].ifd = fd;
	g_in[fd].print = 1;
	g_in[fd].lim = -1;
	if (g_rd[fd] > 0 && ft_ifsrd(g_in + fd, NULL, (size_t)g_rd[fd]) < 0)
		return (WUT);
	if ((g_rd[fd] = ft_ifschr(g_in + fd, 0, '\n', &buf)) > 0)
	{
		if (g_rd[fd] >= UINT16_MAX)
			return (NOP);
		g_ln.len = 0;
		ft_sdsmpush(&g_ln, buf, (size_t)g_rd[fd]);
		if (!ft_stris(g_ln.buf, ft_iscoolc))
			return (ft_ethrow(WUT, EBADF, FT_DBG));
		*ln = g_ln.buf;
		return (YEP);
	}
	if (g_rd[fd] < 0)
		return (WUT);
	return (NOP);
}

static inline size_t	catmiddle(char c, ssize_t rd, char *buf)
{
	size_t	middle;

	if (c < 0)
	{
		middle = g_ln.len + c;
		ft_sdsnpop(&g_ln, (size_t)-c, NULL);
	}
	else if (c)
	{
		middle = g_ln.len + 1;
		ft_sdscpush(&g_ln, c);
	}
	else
		middle = g_ln.len;
	ft_sdsmpush(&g_ln, buf, (size_t)rd);
	return (middle);
}

inline int				rl_catnotty(int fd, char **ln, char c, char **it)
{
	char	*buf;
	size_t	middle;

	if (fd < 0 || fd > OPEN_MAX)
		return (ft_ethrow(WUT, EINVAL, FT_DBG));
	g_in[fd].ifd = fd;
	if (g_rd[fd] > 0 && ft_ifsrd(g_in + fd, NULL, (size_t)g_rd[fd]) < 0)
		return (WUT);
	if ((g_rd[fd] = ft_ifschr(g_in + fd, 0, '\n', &buf)) > 0)
	{
		if (g_rd[fd] >= UINT16_MAX)
			return (NOP);
		middle = catmiddle(c, g_rd[fd], buf);
		*ln = g_ln.buf;
		*it = g_ln.buf + middle;
		return (YEP);
	}
	if (g_rd[fd] < 0)
		return (WUT);
	return (NOP);
}
