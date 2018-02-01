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

#include "ush/bi/read.h"

int		sh_bireadgetdelim(char *optarg, t_read *data)
{
	if (!optarg)
		return (NOP);
	if (data)
		data->delim = *optarg;
	return (YEP);
}

int		sh_bireadgetnchars(char *optarg, t_read *data)
{
	if (!optarg)
		return (NOP);
	if (data)
		data->nchars = ft_atoi(optarg);
	return (YEP);
}

int		sh_bireadgetprompt(char *optarg, t_read *data)
{
	if (!optarg)
		return (NOP);
	if (data)
		data->prompt = optarg;
	return (YEP);
}

int		sh_bireadgettimeout(char *optarg, t_read *data)
{
	if (!optarg)
		return (NOP);
	if (data)
		data->timeout = ft_atoi(optarg);
	return (YEP);
}

int		sh_bireadgetfd(char *optarg, t_read *data)
{
	if (!optarg)
		return (NOP);
	if (data)
		data->fd = ft_atoi(optarg);
	return (YEP);
}