/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:39:49 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>

#include "msh.h"

static inline char	*msh_cwd(t_msh *self)
{
	size_t	l;
	char	cwd[4096 + 1];
	char	*p;
	char	**home;
	char	*h;

	p = getcwd(cwd, 4096);
	if (!p || !(home = msh_getenv(self, "HOME")))
		return (NULL);
	h = *home + 5;
	if (!ft_strbegw(h, p))
		return (p);
	if (p[l = ft_strlen(h)] != '\0')
		ft_memmove(p + 1, p + l, (ft_strlen(p) - l + 1) * sizeof(char));
	else
		p[1] = '\0';
	*p = '~';
	return (p);
}

inline t_ret		msh_prompt(t_msh *self, char *prompt)
{
	char *cwd;

	if (!(cwd = msh_cwd(self)))
		return (RET_ERR);
	ft_puts(1, cwd);
	ft_puts(1, prompt);
	return (RET_OK);
}

inline t_ret		msh_av(t_msh *self, t_vstr *av, char *exe)
{
	t_tok *end;

	ft_vstr_ctor(av);
	if (!ft_vstr_pushc(av, exe))
		return (RET_ERR);
	while ((end = msh_peek(self)) && end->id)
	{
		if (end->id == MSH_TOK_WORD &&
			!ft_vstr_pushc(av, ft_tok_ident(end)->buf))
			return (RET_ERR);
		else if (end->id != MSH_TOK_WORD && !ft_strchr(" \t", end->id))
			break ;
		msh_next(self, NULL);
	}
	if (!ft_vstr_grow(av, 1))
		return (RET_ERR);
	FT_INIT(ft_vstr_end(av), char *);
	return (RET_OK);
}

inline t_ret		msh_path_lookup(t_msh *self, char *f, int mode, char ret[])
{
	char		**path;
	char		*beg;
	char		*sep;
	struct stat	s;

	if (!*f)
		return (RET_NOK);
	if (*f == '/' && ft_strcpy(ret, f))
		return (RET_OK);
	if (!(path = msh_getenv(self, "PATH")))
		return (RET_NOK);
	beg = *path + 5;
	while ((sep = ft_strchr(beg, ':')))
	{
		ft_strncpy(ret, beg, sep - beg)[sep - beg] = '\0';
		ft_pathcat(ret, f);
		if (lstat(ret, &s) == 0 && (s.st_mode & mode))
			return (RET_OK);
		beg = sep + 1;
	}
	return (RET_NOK);
}
