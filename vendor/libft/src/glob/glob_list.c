/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:57:56 by mc                #+#    #+#             */
/*   Updated: 2018/02/13 10:04:57 by mc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_climb_tree.h"

t_match	*matchctor(char const *path, size_t len)
{
	t_match *new;

/*
		if ((flags & GLOB_MARK))
			append_slash_to_each_name();
*/

	if (!(new = malloc(sizeof(t_match) + len)))
		return (NULL);

	ft_bzero(new, sizeof(t_match));
	ft_memcpy(new->buf, path, len);

	return (new);
}

void	matchdtor(t_match *match)
{
	t_match *prev;

	if (!match)
		return;
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

t_bool	add_match_to_list(t_match *match, t_match *match_list, int flags)
{
	(void)match; //TODO
	(void)match_list; //TODO

	return TRUE;
}

size_t	list_len(t_match *match_list)
{
	int ret;

	ret = 0;
	while (match_list)
	{
		ret++;
		match_list = match_list->next;
	}

	return ret;
}
