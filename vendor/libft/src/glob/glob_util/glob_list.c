/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:57:56 by mc                #+#    #+#             */
/*   Updated: 2018/02/20 17:19:43 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

t_match	*matchctor(char const *path, size_t len)
{
	t_match *new;

	if (!(new = malloc(sizeof(t_match) + len)))
		return ((NULL));
	ft_bzero(new, sizeof(t_match) + len);
	ft_memcpy(new->buf, path, len);
	return (new);
}

void	matchdtor(t_match *match)
{
	t_match *prev;

	if (!match)
		return ;
	prev = match;
	match = match->next;
	free(prev);
	while (match)
	{
		prev = match;
		match = match->next;
		free(prev);
	}
}

void	add_match_to_list(t_match *match, t_match **match_list)
{
	match->next = *match_list;
	*match_list = match;
}

size_t	list_len(t_match *match_list)
{
	size_t	ret;

	ret = 0;
	while (match_list)
	{
		ret++;
		match_list = match_list->next;
	}
	return (ret);
}
