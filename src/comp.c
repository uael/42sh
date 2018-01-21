/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>

#include "ush/shell.h"

inline void		sh_complete(t_sds *cmd)
{
	char			*word;
	char			*end;
	char			cwd[PATH_MAX];
	char			match[PATH_MAX] = { 0 };
	DIR				*dir;
	struct dirent	*dirent;
	int				top;
	char			*path;
	char			wcpy[PATH_MAX];
	char			*w;
	char			*chr;
	int 			i;
	int 			cur;
	int				midsir;
	size_t			len;

	end = cmd->len ? cmd->buf + cmd->len - 1 : cmd->buf;
	word = end;
	if (*word && ft_strchr(sh_varifs(), *word))
		return ;
	while (word > cmd->buf && !ft_strchr(sh_varifs(), *(word - 1)))
		--word;
	if ((chr = ft_strrchr(word, '/')))
	{
		if (ft_strcmp("/", word))
			*chr = '\0';
		if (!(dir = opendir(word)))
			return ;
		*chr = '/';
		word = chr + 1;
	}
	else if (!getcwd(cwd, PATH_MAX) || !(dir = opendir(cwd)))
		return ;
	top = -1;
	midsir = 0;
	while ((dirent = readdir(dir)))
	{
		i = 0;
		cur = 0;
		path = dirent->d_name;
		if (!*wcpy && *path != '.')
		{
			if (dirent->d_type == DT_DIR)
				midsir = 0;
			ft_strcpy(match, dirent->d_name);
			break ;
		}
		len = ft_strlen(ft_strcpy(wcpy, word));
		if (wcpy[len - 1] == '/')
			wcpy[len - 1] = 0;
		w = wcpy;
		if (!ft_strcmp(w, path))
			continue ;
		while (*path)
		{
			if (*path == *w)
			{
				if (i == 0)
					cur += 10;
				else if (i == 1)
					cur += 9;
				if (i == 3)
					cur += 8;
				if (i == 4)
					cur += 7;
				if (i == 5)
					cur += 6;
				if (i == 6)
					cur += 4;
				if (i == 7)
					cur += 3;
				if (i == 8)
					cur += 2;
				if (i == 9)
					cur += 1;
				++i;
				++path;
				++w;
			}
			else
			{
				++i;
				++path;
			}
		}
		if (cur && cur > top)
		{
			top = cur;
			if (dirent->d_type == DT_DIR)
				midsir = 1;
			ft_strcpy(match, dirent->d_name);
		}
	}
	if (*match)
	{
		cmd->len = word - cmd->buf;
		ft_sdsapd(cmd, match);
		if (midsir && cmd->buf[cmd->len - 1] != '/')
			ft_sdscpush(cmd, '/');
	}
	closedir(dir);
}
