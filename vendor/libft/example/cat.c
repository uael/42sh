/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example/cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	g_fd;

static int	cat_exhdl(int rcode, void *arg)
{
	if (!errno)
		return (rcode);
	if (arg)
		ft_putf(2, COLOR_BRED"cat: "COLOR_RESET"%s: %e\n", arg, errno);
	else
		ft_putf(2, COLOR_BRED"cat: "COLOR_RESET"%e\n", errno);
	if (g_fd > 0)
		close(g_fd);
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_ifs	*in;
	t_ofs	*out;
	ssize_t	sz;
	char	*ln;

	if (ac > 3)
		return (ENO_THROW(EXIT_FAILURE, E2BIG));
	ft_exbind(EXALL, ft_exhdl(cat_exhdl, ac < 2 ? NULL : av[1]), NULL);
	if (ac < 2)
		g_fd = STDIN_FILENO;
	else if ((g_fd = open(av[1], O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		return (THROW(EXIT_FAILURE));
	ft_ifsctor(in = alloca(sizeof(t_ifs)), g_fd);
	ft_ofsctor(out = alloca(sizeof(t_ofs)), STDOUT_FILENO);
	while ((sz = ft_ifschr(in, '\n', &ln)) > 0)
		ft_ofswr(out, ln, (size_t)ft_ifsrd(in, NULL, (size_t)sz));
	ft_ofsflush(out);
	if (close(g_fd))
		return (THROW(EXIT_FAILURE));
	return (EXIT_SUCCESS);
}