/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp/param/subst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2018/01/06 11:10:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fnmatch.h>

#include "ush/exp.h"
#include "ush/shell.h"

int	sh_expparamsubst(t_sds *word, char **words, t_vec *av, t_param *p)
{
	char buf[21];
	char *value;
	char *nvalue;
	uint8_t	l;
	int		n;
	size_t	len;
	char	*beg;
	char	*end;
	char	*next;
	int		i;
	t_bool	freev;
	t_bool	expp;

	if (*p->start == '{' && **words != '}')
		return (sh_expparamdone(p, NOP, NULL, 0));
	freev = 0;
	if (!p->env.len)
	{
		if (p->hash)
		{
			l = ft_intstr(buf, g_sh->ac, 10);
			buf[l] = '\0';
			value = buf;
		}
		else
		{
			*words = p->start - 1;
			*ft_sdspush(word) = '$';
			return (2);
		}
	}
	else if (ft_isdigit(*p->env.buf))
	{
		if ((n = (int)ft_atoi(p->env.buf)) > g_sh->ac)
			value = 0;
		else
			value = g_sh->av[n];
	}
	else if (p->special)
	{
		if (*p->env.buf == '$')
		{
			l = ft_intstr(buf, g_sh->pid, 10);
			buf[l] = '\0';
			value = buf;
		}
		else if ((*p->env.buf == '*' || *p->env.buf == '@') && p->hash)
		{
			l = ft_intstr(buf, g_sh->ac ? g_sh->ac - 1 : 0, 10);
			ft_sdsmpush(word, buf, l);
			ft_sdsdtor(&p->env);
			ft_sdsdtor(&p->pattern);
			return (2);
		}
		else if (*p->env.buf == '*' || (*p->env.buf == '@' && !p->quoted))
		{
			len = 0;
			i = 0;
			while (++i < g_sh->ac)
				len += ft_strlen(g_sh->av[i]) + 1;
			value = ft_malloc(len);
			end = value;
			*end = 0;
			i = 0;
			while (++i < g_sh->ac)
			{
				if (i > 1)
					*end++ = ' ';
				end = ft_stpcpy(end, g_sh->av[i]);
			}
			freev = 1;
		}
		else
		{
			if (g_sh->ac == 2)
				value = g_sh->av[1];
			else if (g_sh->ac > 2)
			{
				ft_sdsapd(word, g_sh->av[1]);
				*(char **)ft_vecpush(av) = ft_strdup(word->buf);
				word->len = 0;
				i = 1;
				while (++i < g_sh->ac - 1)
					*(char **)ft_vecpush(av) = ft_strdup(g_sh->av[i]);
				value = g_sh->av[i];
			}
			else
			{
				ft_sdsdtor(&p->env);
				ft_sdsdtor(&p->pattern);
				return (2);
			}
		}
	}
	else
		value = sh_varget(p->env.buf, environ);
	if (p->act)
	{
		expp = 0;
		if (ACT_ISRP(p->act))
			expp = 1;
		else if (ACT_ISNULL(p->act))
		{
			if (!value || (!*value && p->colon))
				expp = 1;
		}
		else if (value && (*value || !p->colon))
			expp = 1;
		if (expp && p->pattern.len)
		{
			char	*pat;
			int		quoted;

			quoted = 0;
			pat = ft_strcpy(ft_malloc(p->pattern.len + 1), p->pattern.buf) - 1;
			beg = pat + 1;
			p->pattern.len = 0;
			while (*++pat)
			{
				if (*pat == '"')
				{
					if (quoted == 2)
					{
						quoted = 0;
						continue ;
					}
					else if (quoted == 0)
					{
						quoted = 2;
						continue ;
					}
				}
				else if (*pat == '\'')
				{
					if (quoted == 1)
					{
						quoted = 0;
						continue ;
					}
					else if (quoted == 0)
					{
						quoted = 1;
						continue ;
					}
				}
				else if (*pat == '*' || *pat == '?')
				{
					if (quoted)
						*ft_sdspush(&p->pattern) = '\\';
				}
				else if (*pat == '$')
				{
					sh_expdollars(&p->pattern, &pat, NULL, 1);
					continue ;
				}
				else if (*pat == '~')
				{
					if (!quoted && !p->pattern.len)
					{
						sh_exptidle(&p->pattern, &pat, 0);
					}
				}
				else if (*pat == '\\')
				{
					*ft_sdspush(&p->pattern) = '\\';
					++pat;
				}
				*ft_sdspush(&p->pattern) = *pat;
			}
			free(beg);
		}
		if (ACT_ISRP(p->act))
		{
			char *pat;
			char c;

			if (value && p->pattern.len)
			{
				end = value + ft_strlen(value);
				if (p->act == ACT_RP_SHORT_LEFT)
				{
					pat = value - 1;
					while (++pat <= end)
					{
						c = *pat;
						*pat = '\0';
						if (fnmatch(p->pattern.buf, value, 0) != FNM_NOMATCH)
						{
							*pat = c;
							if (freev)
							{
								free(value);
								freev = 0;
							}
							value = pat;
							break ;
						}
						*pat = c;
					}
				}
				else if (p->act == ACT_RP_LONG_LEFT)
				{
					pat = end + 1;
					while (--pat >= value)
					{
						c = *pat;
						*pat = '\0';
						if (fnmatch(p->pattern.buf, value, 0) != FNM_NOMATCH)
						{
							*pat = c;
							if (freev)
							{
								free(value);
								freev = 0;
							}
							value = pat;
							break ;
						}
						*pat = c;
					}
				}
				else if (p->act == ACT_RP_SHORT_RIGHT)
				{
					pat = end + 1;
					while (--pat >= value)
					{
						if (fnmatch(p->pattern.buf, value, 0) != FNM_NOMATCH)
						{
							nvalue = ft_malloc(pat - value + 1);
							ft_strncpy(nvalue, value, pat - value);
							if (freev)
								free(value);
							freev = 1;
							value = nvalue;
							break ;
						}
					}
				}
				else if (p->act == ACT_RP_LONG_RIGHT)
				{
					pat = value - 1;
					while (++pat <= end)
					{
						if (fnmatch(p->pattern.buf, value, 0) != FNM_NOMATCH)
						{
							nvalue = ft_malloc(pat - value + 1);
							ft_strncpy(nvalue, value, pat - value);
							if (freev)
								free(value);
							freev = 1;
							value = nvalue;
							break ;
						}
					}
				}
			}
		}
		else if (p->act == ACT_NULL_ERROR)
		{
			if (value && *value)
			{
				if (p->colon)
				{
					if (!p->pattern.len)
						ft_sdsapd(&p->pattern, "parameter null or not set");
					ft_putf(1, "%s: %s", p->env.buf, p->pattern.buf);
				}
				if (freev)
					free(value);
				ft_sdsdtor(&p->env);
				ft_sdsdtor(&p->pattern);
				return (2);
			}
		}
		else if (p->act == ACT_NULL_SUBST)
		{
			if (freev)
				free(value);
			if (!p->colon && value)
			{
				ft_sdsdtor(&p->env);
				ft_sdsdtor(&p->pattern);
				return (2);
			}
			freev = 0;
			value = p->pattern.buf;
		}
		else if (p->act == ACT_NONNULL_SUBST)
		{
			if (value && (*value || p->colon))
			{
				if (freev)
					free(value);
				freev = 0;
				value = p->pattern.buf;
			}
			else
			{
				if (freev)
					free(value);
				ft_sdsdtor(&p->env);
				ft_sdsdtor(&p->pattern);
				return (2);
			}
		}
		else if (p->act == ACT_NULL_ASSIGN)
		{
			if (!value || !*value)
			{
				if (!p->colon && value)
				{
					ft_sdsdtor(&p->env);
					ft_sdsdtor(&p->pattern);
					return (2);
				}
				if (freev)
					free(value);
				freev = 0;
				value = p->pattern.buf;
				sh_varset(p->env.buf, value ? value : "");
			}
		}
	}
	if (p->hash)
	{
		l = ft_intstr(buf, (int64_t)(value ? ft_strlen(value) : 0), 10);
		ft_sdsmpush(word, buf, l);
		if (freev)
			free(value);
		ft_sdsdtor(&p->env);
		ft_sdsdtor(&p->pattern);
		return (2);
	}
	if (!value)
	{
		ft_sdsdtor(&p->env);
		ft_sdsdtor(&p->pattern);
		return (2);
	}
	if (p->quoted || !av)
	{
		ft_sdsapd(word, value);
		if (freev)
			free(value);
		ft_sdsdtor(&p->env);
		ft_sdsdtor(&p->pattern);
		return (2);
	}
	else
	{
		if (!freev)
			value = ft_strdup(value);
		beg = value;
		i = 0;
		while (i || *beg)
		{
			if (beg != value)
			{
				*(char **)ft_vecpush(av) = ft_strdup(word->buf);
				word->len = 0;
			}
			beg += ft_strspn(beg, g_ifsw);
			if (!i && !*beg)
				break ;
			end = beg + ft_strcspn(beg, g_ifs);
			next = end + ft_strspn(end, g_ifsw);
			if ((i = (*next && ft_strchr(g_ifs, *next))))
				++next;
			*end = 0;
			ft_sdsapd(word, beg);
			beg = next;
		}
		free(value);
	}
	ft_sdsdtor(&p->env);
	ft_sdsdtor(&p->pattern);
	return (2);
}
