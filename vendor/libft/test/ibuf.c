/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/ibuf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#define RES ".libft_test.res"
#define TXT "Lorem ipsum dolor sit amet,\nconsectetur adipiscing elit.\n\nAliquam" \
	" fringilla vehicula purus ut rhoncus.\n\nDonec in dapibus ex,\nvitae efficitu" \
	"r dui.\n\nIn bibendum,\nquam vel interdum congue,\nrisus massa bibendum diam,\n" \
	" non aliquam nisi elit nec dui.\n\nNulla porta metus nulla,\nvel posuere neq" \
	"ue malesuada a.\n\nQuisque aliquet nibh urna,\neu malesuada justo dictum por" \
	"ttitor.\n\nMaecenas pretium dolor non risus sodales luctus.\n\nNam et nunc non" \
	" libero efficitur faucibus at quis eros.\n\nEtiam nec tempus nisi.\n\nNunc qua" \
	"m lorem,\ntristique nec bibendum aliquam,\ncursus vel risus.\n\nAenean a erat" \
	" consectetur,\nporttitor turpis id,\nauctor nulla.\n\nSed pellentesque nulla " \
	"in odio egestas,\net finibus erat laoreet.\n\n"

static size_t	g_sz = 0;
static int		g_fd = 0;

int				setup(void)
{
	int		fd;
	ssize_t	wr;

	if ((fd = open(RES, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if ((wr = ft_write(fd, TXT, sizeof(TXT) - 1)) < 0)
		return (WUT);
	g_sz += wr;
	if (close(fd) || (g_fd = open(RES, O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(WUT));
	return (YEP);
}

int				teardown(void)
{
	if (close(g_fd) || remove(RES))
		return (THROW(WUT));
	return (YEP);
}

static int		test_ctor(void)
{
	t_ifs	*buf;

	ft_ifsctor(buf = alloca(sizeof(t_ifs)), g_fd);
	ASSERT(buf);
	ASSERT(buf->ifd == g_fd);
	ASSERT(buf->i == 0);
	ASSERT(buf->rd == 0);
	return (YEP);
}

static int		test_buf(void)
{
	t_ifs	*buf;

	ft_ifsctor(buf = alloca(sizeof(t_ifs)), g_fd);
	ASSERT(ft_ifsbuf(buf, 1, NULL) == 1);
	ASSERT(ft_ifsbuf(buf, 10, NULL) == 10);
	ASSERT(ft_ifsbuf(buf, FT_PAGE_SIZE, NULL) == FT_PAGE_SIZE);
	ASSERT(ft_ifsbuf(buf, FT_PAGE_SIZE * 2, NULL) == g_sz);
	lseek(g_fd, 0, SEEK_SET);
}

static int		test_chr(void)
{
	t_ifs	*buf;
	ssize_t	tsz;
	ssize_t	sz;
	char	*ln;

	ft_ifsctor(buf = alloca(sizeof(t_ifs)), g_fd);
	tsz = 0;
	while ((sz = ft_ifschr(buf, '\n', &ln)) > 0)
	{
		tsz += sz;
		ASSERT(ft_ifsrd(buf, NULL, (size_t)sz) == sz);
	}
	ASSERT(tsz == g_sz);
	lseek(g_fd, 0, SEEK_SET);
}

t_test			g_tests[] =
{
	{"ctor", test_ctor},
	{"buf", test_buf},
	{"chr", test_chr},
	{NULL, NULL}
};