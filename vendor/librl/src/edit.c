/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/11 13:31:59 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "edit.h"
#include "visual.h"
#include "read.h"

#define K_ESC "\x1b"
#define K_BACKSPACE "\x7f"
#define K_DELETE "\x1b\x5b\x33\x7e"
#define K_CTRL_A "\x1"
#define K_CTRL_B "\x2"
#define K_CTRL_C "\x3"
#define K_CTRL_D "\x4"
#define K_CTRL_E "\x5"
#define K_CTRL_F "\x6"
#define K_CTRL_H "\x8"
#define K_TAB "\x9"
#define K_RETURN "\xa"
#define K_CTRL_K "\xb"
#define K_CTRL_L "\xc"
#define K_ENTER "\xd"
#define K_CTRL_P "\x10"
#define K_CTRL_R "\x12"
#define K_CTRL_T "\x14"
#define K_CTRL_U "\x15"
#define K_CTRL_V "\x16"
#define K_UP "\x1b\x5b\x41"
#define K_DOWN "\x1b\x5b\x42"
#define K_RGT "\x1b\x5b\x43"
#define K_LEFT "\x1b\x5b\x44"
#define K_CTRL_UP "\x1b\x5b\x31\x3b\x35\x41"
#define K_CTRL_DOWN "\x1b\x5b\x31\x3b\x35\x42"
#define K_CTRL_RIGHT "\x1b\x5b\x31\x3b\x35\x43"
#define K_CTRL_LEFT "\x1b\x5b\x31\x3b\x35\x44"
#define K_SHT_UP "\x1b\x5b\x31\x3b\x32\x41"
#define K_SHT_DOWN "\x1b\x5b\x31\x3b\x32\x42"
#define K_SHT_RIGHT "\x1b\x5b\x31\x3b\x32\x43"
#define K_SHT_LEFT "\x1b\x5b\x31\x3b\x32\x44"
#define K_OPT_UP "\x1b\x1b\x5b\x41"
#define K_OPT_DOWN "\x1b\x1b\x5b\x42"
#define K_OPT_RIGHT "\x1b\x1b\x5b\x43"
#define K_OPT_LEFT "\x1b\x1b\x5b\x44"
#define K_HOME "\x1b\x5b\x48"
#define K_END "\x1b\x5b\x46"
#define K_CTRL_Y "\x19"

t_editln			g_edit[HIST_MAX + 1] =
{
	{ { 0, 0, 0 }, 0, 0, 0, { NULL, sizeof(char *), 0, 0 } },
};
uint8_t				g_edit_len = 0;
uint8_t				g_edit_idx = 0;
t_editln			*g_eln;
t_bool				g_edit_cat = 0;
char				*g_edit_prompt = 0;

t_rlhook			*g_rlhook = NULL;

static inline int	resetmode(void)
{
	if (g_mode != RL_INSERT)
	{
		g_mode = RL_INSERT;
		rl_editprint();
	}
	return (YEP);
}

static t_editbind	g_inskeymap[] =
{
	{1, K_ESC, resetmode},
	{1, K_RETURN, rl_editreturn},
	{1, K_BACKSPACE, rl_editbackspace},
	{1, K_ENTER, rl_editreturn},
	{1, K_CTRL_B, rl_editbackspace},
    {1, K_CTRL_C, rl_signalc},
	{1, K_CTRL_D, rl_signald},
	{1, K_CTRL_P, rl_visualpaste},
	{1, K_CTRL_L, rl_editclear},
	{1, K_CTRL_V, rl_visualtoggle},
	{1, K_CTRL_Y, rl_visualyank},
	{3, K_LEFT, rl_editleft},
	{3, K_RGT, rl_editright},
	{3, K_UP, rl_editup},
	{3, K_DOWN, rl_editdown},
	{3, K_HOME, rl_edithome},
	{3, K_END, rl_editend},
	{4, K_DELETE, rl_editdelete},
	{4, K_OPT_UP, rl_editctrlup},
	{4, K_OPT_DOWN, rl_editctrldown},
	{4, K_OPT_RIGHT, rl_editctrlright},
	{4, K_OPT_LEFT, rl_editctrlleft},
	{6, K_CTRL_UP, rl_editctrlup},
	{6, K_CTRL_DOWN, rl_editctrldown},
	{6, K_CTRL_RIGHT, rl_editctrlright},
	{6, K_CTRL_LEFT, rl_editctrlleft},
	{6, K_SHT_UP, rl_editctrlup},
	{6, K_SHT_DOWN, rl_editctrldown},
	{6, K_SHT_RIGHT, rl_editctrlright},
	{6, K_SHT_LEFT, rl_editctrlleft},
	{0, NULL, NULL},
};

static t_editbind	g_viskeymap[] =
{
	{1, K_ESC, resetmode},
	{1, K_RETURN, rl_editreturn},
	{1, K_BACKSPACE, rl_editbackspace},
	{1, K_ENTER, rl_editreturn},
	{1, K_CTRL_B, rl_editbackspace},
    {1, K_CTRL_C, rl_signalc},
	{1, K_CTRL_D, rl_signald},
	{1, K_CTRL_P, rl_visualpaste},
	{1, K_CTRL_L, rl_editclear},
	{1, K_CTRL_V, rl_visualtoggle},
	{1, K_CTRL_Y, rl_visualyank},
	{3, K_LEFT, rl_editleft},
	{3, K_RGT, rl_editright},
	{3, K_HOME, rl_edithome},
	{3, K_END, rl_editend},
	{4, K_DELETE, rl_editdelete},
	{4, K_OPT_UP, rl_editctrlup},
	{4, K_OPT_DOWN, rl_editctrldown},
	{4, K_OPT_RIGHT, rl_editctrlright},
	{4, K_OPT_LEFT, rl_editctrlleft},
	{6, K_CTRL_UP, rl_editctrlup},
	{6, K_CTRL_DOWN, rl_editctrldown},
	{6, K_CTRL_RIGHT, rl_editctrlright},
	{6, K_CTRL_LEFT, rl_editctrlleft},
	{6, K_SHT_UP, rl_editctrlup},
	{6, K_SHT_DOWN, rl_editctrldown},
	{6, K_SHT_RIGHT, rl_editctrlright},
	{6, K_SHT_LEFT, rl_editctrlleft},
	{0, NULL, NULL},
};

inline void			rl_editdtor(void)
{
	rl_histdtor();
	g_edit_idx = 0;
	while (g_edit_idx < g_edit_len)
	{
		ft_sdsdtor(&(g_edit + g_edit_idx)->str);
		ft_vecdtor(&(g_edit + g_edit_idx)->rows, NULL);
		++g_edit_idx;
	}
	g_edit_idx = 0;
	g_edit_len = 0;
	g_eln = 0;
}

static inline void	prepare(t_bool cat)
{
	g_edit_len = 0;
	while (rl_histcpy(g_edit_len, &g_edit[g_edit_len].str))
		++g_edit_len;
	g_eln = g_edit +
		(g_edit_idx = g_edit_len++);
	g_eln->str.len = 0;
	ft_sdsgrow(&g_eln->str, 64);
	*g_eln->str.buf = '\0';
	g_eln->idx = 0;
	g_eln->row = 0;
	g_eln->rows.len = 0;
	g_eln->rows.isz = sizeof(char *);
	g_edit_cat = cat;
}

static inline int	keymap(char *key, ssize_t rd)
{
	int			st;
	t_editbind	*bind;

	if (*key == *K_ESC)
	{
		if ((rd = ft_read(STDIN_FILENO, key + 1, 5)) < 0)
			return (WUT);
		++rd;
	}
	st = 2;
	bind = (g_mode == RL_VISUAL ? g_viskeymap : g_inskeymap) - 1;
	while (st == 2 && (++bind)->rd <= rd && bind->rd)
		if (rd == bind->rd && !ft_memcmp(key, bind->key, (size_t)bind->rd))
			st = bind->cb();
	return (st == 2 ? YEP : st);
}

int					rl_editln(char const *p, size_t *sz, char **ln, t_bool cat)
{
	ssize_t		rd;
	char		key[7];
	int			st;

	g_edit_prompt = (char *)p;
	prepare(cat);
	st = YEP;
	while (1)
		if ((rd = ft_read(STDIN_FILENO, key, 1)) < 0)
			return (WUT);
		else if (!rd)
			g_rlhook ? g_rlhook() : 0;
		else if (ft_iscntrl(*key) || !ft_isascii(*key))
		{
			if ((st = keymap(key, rd)))
				break ;
		}
		else if (rl_editinsert(*key))
			break ;
	if (st >= 0)
	{
		*sz = g_eln->str.len;
		*ln = g_eln->str.buf;
	}
	return (st < 0 || st == RL_EXIT ? WUT : YEP);
}
