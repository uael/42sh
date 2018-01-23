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

static char		g_save[PATH_MAX] = { 0 };
static char		g_savein[PATH_MAX] = { 0 };

static int		scorepath(char *path, char *cpath)
{
	int		score;
	char	*pathit;
	char	*cpathit;

	if (!ft_strcmp(g_save, cpath))
		return (0);
	if (!ft_strcmp(path, cpath))
		return (PATH_MAX * PATH_MAX);
	score = 0;
	pathit = path;
	cpathit = cpath;
	while (*cpathit && *pathit)
		if (*cpathit != *pathit)
			++cpathit;
		else
		{
			if ((cpathit++ - cpath) <= (pathit++ - path))
				score += PATH_MAX - (cpathit - cpath - 1);
		}
	if ((score -= ft_strlen(cpath) - ft_strlen(path)) <= 0)
		return (0);
	return (score);
}

static int		candidatedir(char *path, char *in, int sc, char *buf)
{
	DIR				*dir;
	struct dirent	*ent;
	int				csc;
	int				next;

	if (!in || !(dir = opendir(in)))
		return (sc);
	next = 0;
	while ((ent = readdir(dir)))
		if (!ft_strcmp(".", ent->d_name) || !ft_strcmp("..", ent->d_name))
			continue ;
		else if (!*path || next)
			return (ft_strcpy(buf, ent->d_name) &&
				ft_strcpy(g_savein, in) && !closedir(dir));
		else if (!ft_strcmp(g_savein, in) && !ft_strcmp(g_save, ent->d_name)
			&& !ft_strcmp(g_save, path))
			next = 1;
		else if (((csc = ent->d_type == DT_DIR ? 2 : 0) & 0))
			;
		else if ((csc += scorepath(path, ent->d_name)) > sc && (sc = csc))
			(void)(ft_strcpy(buf, ent->d_name) && ft_strcpy(g_savein, in));
	closedir(dir);
	return (next ? candidatedir("", in, 0, buf) : sc);
}

static int		candidatepath(char *path, char *pvar, int score, char *buf)
{
	char		*sep;
	size_t		len;
	char		pbuf[PATH_MAX];

	if (!pvar)
		return (score);
	while (1)
	{
		sep = ft_strchr(pvar, ':');
		len = sep ? (size_t)(sep - pvar) : ft_strlen(pvar);
		ft_strncpy(pbuf, pvar, len)[len] = '\0';
		score = candidatedir(path, pbuf, score, buf);
		if (!sep)
			break ;
		pvar = sep + 1;
	}
	return (score);
}

static char		*completepath(char *sep, char *path, char *buf)
{
	char		dir[PATH_MAX];

	if (sep == path)
		ft_strcpy(dir, "/");
	else
	{
		*sep = '\0';
		ft_strcpy(dir, path);
		*sep = '/';
	}
	path = sep + 1;
	candidatedir(path, dir, 0, buf);
	return (path);
}

inline void		sh_complete(t_sds *cmd)
{
	char	*word;
	char	*end;
	char	cwd[PATH_MAX];
	char	*in;
	char	match[PATH_MAX];

	end = cmd->len ? cmd->buf + cmd->len - 1 : cmd->buf;
	word = end;
	if (*word && ft_strchr(sh_varifs(), *word))
		word = cmd->buf + cmd->len;
	else
		while (word > cmd->buf && !ft_strchr(sh_varifs(), *(word - 1)))
			--word;
	if ((end = ft_strrchr(word, '/')))
		word = completepath(end, word, match);
	else if ((!ft_strcmp(in = getcwd(cwd, PATH_MAX), g_savein) &&
		!ft_strcmp(g_save, word)) || !*word)
		candidatedir(word, in, *match = 0, match);
	else
		candidatepath(word, sh_getenv("PATH"), candidatedir(word, getcwd(cwd,
			PATH_MAX), *match = 0, match) + 1, match);
	if (*match && !((cmd->len = word - cmd->buf) & 0))
		ft_sdsapd(cmd, ft_strcpy(g_save, match));
}
