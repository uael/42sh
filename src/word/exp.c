/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word/exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ush/word.h"
#include "ush/shell.h"
#include "ush/eval.h"

static char *g_ifs;
static char g_ifsw[4];
static char *g_origin;

int expbackslash(t_sds *word, char **words, t_bool quote)
{

}

int expdollars(t_sds *word, char **words, t_vec *av, char quote)
{

}

int	expcommchild(char *ln)
{
	t_scope	*sh;
	int		st;
	char	*it;

	sh = g_sh;
	sh_scope();
	ft_memcpy(g_sh, sh, sizeof(t_scope));
	it = ln;
	while (!sh_lex(-1, &it, &ln, sh_eval))
		;
	st = g_sh->status;
	sh_unscope();
	return (sh_exit(st, NULL));
}

void	readproc(int fd, t_sds *word, t_vec *av)
{
	ssize_t	ret;
	char	buf[128 + 1];
	char	*out;
	int		copying;
	int		eol;

	eol = 0;
	copying = 0;
	while ((ret = read(fd, buf, 128)) > 0)
		if (!av)
		{
			eol += ret;
			ft_sdsmpush(word, buf, (size_t)ret);
		}
		else
		{
			buf[ret] = '\0';
			out = buf - 1;
			while (*++out)
				if (ft_strchr(g_ifs, *out))
				{
					if (!ft_strchr(g_ifsw, *out))
					{
						if (copying == 2)
						{
							copying = 0;
							continue;
						}
						copying = 0;
					}
					else
					{
						if (*out == '\n')
						{
							if (copying == 1)
								copying = 3;
							continue ;
						}
						else
						{
							if (copying != 1 && copying != 3)
								continue ;
							copying = 2;
						}
					}
					*(char **)ft_vecpush(av) = ft_strdup(word->len ? word->buf : "");
					word->len = 0;
				}
				else
				{
					if (copying == 3)
					{
						*(char **)ft_vecpush(av) = ft_strdup(word->len ? word->buf : "");
						word->len = 0;
					}
					copying = 1;
					if (*out == '\n')
						++eol;
					else
						eol = 0;
					*ft_sdspush(word) = *out;
				}
		}
	while (eol-- && word->len > 0 && *ft_sdsback(word) == '\n')
		word->buf[--word->len] = '\0';
}

int	expcomm(t_sds *word, t_sds *comm, t_vec *av)
{
	t_proc	proc;
	int		fds[2];
	int		io[3];
	int		status;

	if (!comm->len)
		return (0);
	ps_procfn(&proc, (t_proccb *)expcommchild, (t_dtor)free, comm->buf);
	ft_memcpy(io, STD_FILENOS, 3 * sizeof(int));
	if (pipe(fds) < 0)
		sh_exit(THROW(WUT), NULL);
	io[STDOUT_FILENO] = fds[1];
	proc.close = fds[0];
	proc.child = 1;
	if (ps_procfork(&proc, NULL, io, 1))
		return (YEP);
	waitpid(-proc.pid, &status, WUNTRACED);
	close(fds[1]);
	readproc(fds[0], word, av);
	close(fds[0]);
	ps_procdtor(&proc);
	return (YEP);
}

int expbacktick(t_sds *word, char **words, t_vec *av)
{
	t_sds	comm;
	t_bool	quote;

	quote = 0;
	ft_sdsctor(&comm);
	--*words;
	while (*++*words)
		if (**words == '`')
			return (expcomm(word, &comm, av));
		else if (**words == '\\')
			expbackslash(&comm, words, quote);
		else if (**words == '\'')
			quote ^= 1;
		else
			*ft_sdspush(&comm) = **words;
	return (NOP);
}

int expdquote(t_sds *word, char **words, t_vec *av)
{
	--*words;
	while (*++*words)
		if (**words == '"')
			return (YEP);
		else if (**words == '$')
			expdollars(word, words, av, 1);
		else if (**words == '`')
		{
			++*words;
			expbacktick(word, words, av);
		}
		else if (**words == '\\')
			expbackslash(word, words, 1);
		else
			*ft_sdspush(word) = **words;
	return (NOP);
}

int expsquote(t_sds *word, char **words)
{

}

int exptidle(t_sds *word, char **words, size_t wc)
{

}

int expglob(t_sds *word, char **words, t_vec *av)
{

}

int expbrace(t_sds *word, char **words, t_vec *av)
{

}

void	expifs()
{
	char *ifsch;
	char *whch;
	char *runp;

	if (!(g_ifs = getenv("IFS")))
		g_ifs = ft_strcpy(g_ifsw, " \t\n");
	else
	{
		ft_bzero(g_ifsw, 4);
		ifsch = g_ifs;
		whch = g_ifsw;
		while (*ifsch)
		{
			if (*ifsch == ' ' || *ifsch == '\t' || *ifsch == '\n')
			{
				runp = g_ifsw;
				while (runp < whch && *runp != *ifsch)
					++runp;
				if (runp == whch)
					*whch++ = *ifsch;
			}
			++ifsch;
		}
		*whch = '\0';
	}
}

int sh_wordexp(t_vec *av, char const *src, size_t n, t_bool quote)
{
	t_sds	word;
	char	*words;

	words = alloca(n + (quote ? 3 : 1));
	if (quote)
	{
		*words = '"';
		ft_memcpy(words + 1, src, n);
		*(words + n + 1) = '"';
		*(words + n + 2) = '\0';
	}
	else
		ft_strncpy(words, src, n);
	expifs();
	g_origin = words;
	ft_sdsctor(&word);
	--words;
	while (*++words)
		if (*words == '\\')
			expbackslash(&word, &words, 0);
		else if (*words == '$')
			expdollars(&word, &words, av, quote);
		else if (*words == '`')
		{
			++words;
			expbacktick(&word, &words, av);
		}
		else if (*words == '"')
		{
			++words;
			expdquote(&word, &words, av);
			if (!word.len)
				*(char **)ft_vecpush(av) = ft_strdup("");
		}
		else if (*words == '\'')
		{
			++words;
			expsquote(&word, &words);
			if (!word.len)
				*(char **)ft_vecpush(av) = ft_strdup("");
		}
		else if (*words == '~')
			exptidle(&word, &words, av->len);
		else if (*words == '{')
			expbrace(&word, &words, av);
		else if (ft_strchr("*[?", *words))
			expglob(&word, &words, av);
		else if (ft_strchr(" \t", *words))
		{
			*(char **)ft_vecpush(av) = ft_strdup(word.len ? word.buf : "");
			word.len = 0;
		}
		else
			*ft_sdspush(&word) = *words;
	return (0);
}
