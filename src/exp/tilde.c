/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/comm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>

#include "ush/exp.h"
#include "ush/var.h"

static void	exptilde(t_sds *word)
{
	struct passwd	pwd;
	struct passwd	*tpwd;
	char*			home;
	char			buffer[PATH_MAX];

	if ((home = sh_varget("HOME", g_env)))
		ft_sdsapd(word, home);
	else
	{
		if (getpwuid_r(getuid(), &pwd, buffer, PATH_MAX, &tpwd))
			*ft_sdspush(word) = '~';
		else if (tpwd != NULL && pwd.pw_dir != NULL)
			ft_sdsapd(word, pwd.pw_dir);
		else
			*ft_sdspush(word) = '~';
	}
}

static void	exptildeuser(t_sds *word, char **words, size_t i)
{
	struct passwd	pwd;
	struct passwd	*tpwd;
	char*			user;
	char			buffer[PATH_MAX];

	user = ft_strndup(*words + 1, i);
	if (getpwnam_r(user, &pwd, buffer, PATH_MAX, &tpwd))
		ft_sdsmpush(word, *words, i + 1);
	else if (tpwd != NULL && pwd.pw_dir)
		ft_sdsapd(word, pwd.pw_dir);
	else
		ft_sdsmpush(word, *words, i + 1);
	free(user);
	*words += i - 1;
}

int			sh_exptilde(t_sds *word, char **words, size_t wordc)
{
	size_t i;

	if (word->len && !(*(*words - 1) == '=' && wordc == 0) &&
		!(*(*words - 1) == ':' && ft_strchr(word->buf, '=') && wordc == 0))
	{
		*ft_sdspush(word) = '~';
		return (YEP);
	}
	i = 0;
	while ((*words)[++i])
	{
		if ((*words)[i] == ':' || (*words)[i] == '/' || (*words)[i] == ' ' ||
			(*words)[i] == '\t' || (*words)[i] == 0 )
			break ;
		if ((*words)[i] == '\\')
		{
			*ft_sdspush(word) = '~';
			return (YEP);
		}
	}
	if (i == 1)
		exptilde(word);
	else
		exptildeuser(word, words, i);
	return (YEP);
}
