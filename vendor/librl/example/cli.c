/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example/cli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <librl.h>

int main(void)
{
	t_rl	*rl;
	char	*line;

	rl = alloca(sizeof(t_rl));
	if (rl_ctor(rl, STDIN_FILENO, STDOUT_FILENO, 1))
		return (THROW(WUT));
	while ((line = rl_readline(rl, "$> ")))
		ft_putf(1, "line: '%s'\n", line);
	return (0);
}
