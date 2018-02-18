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

static char *g_ifs;
static char *g_origin;

int expbackslash(t_sds *word, char **words)
{

}

int expdollars(t_sds *word, char **words, t_vec *av, char quote)
{

}

int expbacktick(t_sds *word, char **words, t_vec *av)
{

}

int expdquote(t_sds *word, char **words, t_vec *av)
{

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

int sh_wordexp(t_vec *av, char const *src, size_t n, t_bool quote)
{
	t_sds word;
	char *words;

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
	if (!(g_ifs = getenv("IFS")))
		g_ifs = " \t\n";
	g_origin = words;
	ft_sdsctor(&word);
	while (*words)
		if (*words == '\\')
			expbackslash(&word, &words);
		else if (*words == '$')
			expdollars(&word, &words, av, quote);
		else if (*words == '`')
			expbacktick(&word, &words, av);
		else if (*words == '"')
		{
			expdquote(&word, &words, av);
			if (!word.len)
				*(char **)ft_vecpush(av) = ft_strdup("");
		}
		else if (*words == '\'')
		{
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
			*ft_sdspush(&word) = *words++;
	return (0);
}
