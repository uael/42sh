/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/bi/read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/bi.h"
#include "ush/var.h"

#define USAGE "read [-rs] [-u fd] [-t timeout] [-p prompt]"
#define USAGE1 USAGE " [-n nchars] [-d delim] [name ...]"

static int			sh_readloop(t_read *data)
{
	int		i;
	int		esc;
	int		ret;
	char	buf[2];

	esc = 0;
	if (!(i = 0) && data->prompt && (data->flag & BI_READINTER))
		ft_puts(1, data->prompt);
	while (1)
	{
		if ((ret = read(data->fd, buf, 4)) <= 0)
			return (ret);
		buf[ret] = 0;
		ft_putc(1, data->flag & BI_READLS ? 0 : *buf);
		if (!esc && *buf == data->delim)
			break ;
		esc = esc ? 0 : !(data->flag & BI_READLR) && (*buf == '\\');
		ft_sdsapd(&data->input, buf);
		if (*buf == '\n' && !(data->flag &
			(BI_READLR | BI_READLS | BI_READINTER)))
			ft_puts(1, "> ");
		if ((data->flag & BI_READLN) && ++i >= data->nchars)
			break ;
	}
	return (YEP);
}

static int			sh_readassign(t_read *data)
{
	t_sds	input;
	char	**names;
	char	*ifs;
	char	*tok;

	input = data->input;
	names = *data->names ? data->names : (char*[]){"REPLY", NULL};
	ifs = sh_varifs();
	if (!names[1])
		ifs = NULL;
	tok = ft_strtok(input.buf, ifs);
	while (*names)
	{
		sh_setenv(*names, tok);
		ifs = (++names)[1] ? ifs : NULL;
		tok = ft_strtok(NULL, ifs);
	}
	return (0);
}

static int			sh_readinit(t_read *data, char **av)
{
	(void)av;
	data->flag = 0;
	data->delim = '\n';
	data->nchars = -1;
	data->prompt = NULL;
	data->fd = 0;
	data->timeout = 0;
	data->names = 0;
	ft_sdsctor(&data->input);
	if (isatty(STDIN_FILENO))
		data->flag |= BI_READINTER;
	if (sh_bireadterminit(data) < 0)
		return (EXIT_FAILURE);
	return (0);
}

inline int	sh_biread(int ac, char **av, char **env)
{
	t_read	data;
	int		ret;

	(void)ac;
	(void)env;
	if ((ret = sh_readinit(&data, av)) != 0)
		ft_putf(2, "usage: %s", USAGE1);
	else if ((ret = sh_readloop(&data)))
		;
	else if (data.input.len && (ret = sh_readassign(&data)))
		;
	sh_bireadexit(&data);
	return (ret);
}