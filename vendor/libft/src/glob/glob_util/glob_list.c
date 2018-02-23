/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 09:57:56 by mc                #+#    #+#             */
/*   Updated: 2018/02/23 20:37:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_util.h"

static void	sprglbcp(char *dst, char const *path)
{
	char		quote;
	char		bckslsh;
	char const	*p;

	p = path;
	quote = 0;
	bckslsh = 0;
	while (*p)
	{
		if (*p == '\'' && quote == '\'')
			quote = 0;
		else if (*p == '"' && quote == '"')
			quote = 0;
		else if (*p == '\'' && !quote)
			quote = '\'';
		else if (*p == '"' && !quote)
			quote = '"';
		else if (bckslsh)
			;
		else if (*p == '\\')
			bckslsh = 1;
		*dst = *p;
		dst++;
		p++;
	}
}

t_match		*matchctor(char const *path, size_t len)
{
	t_match *new;

	if (!(new = malloc(sizeof(t_match) + len)))
		return ((NULL));
	ft_bzero(new, sizeof(t_match) + len);
	sprglbcp((char *)new->buf, path);
	return (new);
}

void		matchdtor(t_match *match)
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

void		add_match_to_list(t_match *match, t_match **match_list)
{
	match->next = *match_list;
	*match_list = match;
}

size_t		list_len(t_match *match_list)
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
