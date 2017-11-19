/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/18 19:43:27 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFF_SIZE (4096)

int	msh_dtor(int exitc, t_dstr *cmd)
{
	ft_dstr_dtor(cmd, NULL);
	return (exitc);
}

int msh_echo(char *cmd)
{
	char *s;

	s = NULL;
	while (*cmd && *cmd == ' ')
		++cmd;
	if (*cmd == '\'' && (s = ft_strchr(++cmd, '\'')))
		return ((*(s + 1) && *(s + 1) != ' ') ||
			write(1, cmd, s - 1 - cmd) <= 0 || ft_putc(1, '\n') <= 0);
	else if (*cmd == '\"' && (s = ft_strchr(++cmd, '\"')))
	{
		while (*(s - 1) == '\\')
			s = ft_strchr(s ? s + 1 : ++cmd, '\"');
		return ((*(s + 1) && *(s + 1) != ' ') ||
				write(1, cmd, s - 1 - cmd) <= 0 || ft_putc(1, '\n') <= 0);
	}
	return (ft_putl(1, cmd) <= 0);
}

int	msh_cmd(char *cmd)
{
	char *av;

	if (!(av = ft_strchr(cmd, ' ')))
		return (1);
	if (ft_strncmp("echo ", cmd, 4) == 0)
		return (msh_echo(++av));
	return (1);
}

int	main(void)
{
	char	buf[BUFF_SIZE + 1];
	t_dstr	cmd;
	ssize_t	r;
	char	*eol;

	ft_memset(&cmd, (int)(eol = NULL), sizeof(t_dstr));
	while (1)
		if (write(1, "$> ", 3) < 0)
			return (msh_dtor(EXIT_FAILURE, &cmd));
		else if ((!cmd.len || (eol || !(eol = ft_strchr(cmd.buf, '\n')))) &&
			(r = read(0, buf, BUFF_SIZE)) == 0)
			return (msh_dtor(EXIT_SUCCESS, &cmd));
		else if (r == -1 || !(eol = ft_dstr_pushnc(&cmd, buf, (size_t)r)))
			return (msh_dtor(EXIT_FAILURE, &cmd));
		else if (!(eol = ft_strchr(eol, '\n')))
			return (msh_dtor(EXIT_SUCCESS, &cmd));
		else
		{
			*eol = '\0';
			if (msh_cmd(cmd.buf))
				ft_putl(2, "msh: parse error");
			ft_dstr_shiftn(&cmd, (size_t)r, NULL);
		}
}
