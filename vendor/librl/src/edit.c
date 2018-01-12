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

#include "edit.h"

#define K_BACKSPACE "\x7f"
#define K_DELETE "\x1b\x5b\x33\x7e"
#define K_CTRL_A "\x1"
#define K_CTRL_B "\x2"
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
#define K_UP "\x1b\x5b\x41"
#define K_DOWN "\x1b\x5b\x42"
#define K_RGT "\x1b\x5b\x43"
#define K_LEFT "\x1b\x5b\x44"
#define K_CTRL_UP "\x1b\x5b\x31\x3b\x35\x41"
#define K_CTRL_DOWN "\x1b\x5b\x31\x3b\x35\x42"
#define K_CTRL_RIGHT "\x1b\x5b\x31\x3b\x35\x43"
#define K_CTRL_LEFT "\x1b\x5b\x31\x3b\x35\x44"
#define K_HOME "\x1b\x5b\x48"
#define K_END "\x1b\x5b\x46"
#define K_CTRL_Y "\x19"

t_editln			g_edit[HIST_MAX + 1] = { { { 0, 0, 0 }, 0, 0, 0 } };
uint8_t				g_edit_len = 0;
uint8_t				g_edit_idx = 0;
t_editln			*g_editln;

static t_editbind	g_inskeymap[] =
{
	{1, K_RETURN, rl_editreturn},
	/*{1, K_BACKSPACE, NULL},*/
	{1, K_ENTER, rl_editreturn},
	/*{1, K_CTRL_A, NULL},
	{1, K_CTRL_B, NULL},
	{1, K_CTRL_D, NULL},
	{1, K_CTRL_E, NULL},
	{1, K_CTRL_F, NULL},
	{1, K_CTRL_H, NULL},
	{1, K_TAB, NULL},
	{1, K_CTRL_P, NULL},
	{1, K_CTRL_R, NULL},
	{1, K_CTRL_T, NULL},
	{1, K_CTRL_U, NULL},*/
	{3, K_LEFT, rl_editleft},
	{3, K_RGT, rl_editright},
	{3, K_UP, rl_editup},
	{3, K_DOWN, rl_editdown},
	{3, K_HOME, rl_edithome},
	{3, K_END, rl_editend},
	/*{4, K_DELETE, NULL},
	{6, K_CTRL_UP, NULL},
	{6, K_CTRL_DOWN, NULL},
	{6, K_CTRL_RIGHT, NULL},
	{6, K_CTRL_LEFT, NULL},*/
	{0, NULL, NULL},
};

inline void		rl_editdtor(void)
{
	rl_histexit();
	g_edit_idx = 0;
	while (g_edit_idx < g_edit_len)
		ft_sdsdtor(&(g_edit + g_edit_idx++)->str);
	g_edit_idx = 0;
	g_edit_len = 0;
	g_editln = 0;
}

char			*rl_editln(char const *prompt, size_t *len)
{
	ssize_t		rd;
	char		key[6];
	int			st;
	t_editbind	*bind;

	g_edit_len = 0;
	while (rl_histcpy(g_edit_len, &g_edit[g_edit_len].str))
		++g_edit_len;
	g_editln = g_edit + (g_edit_idx = g_edit_len++);
	g_editln->str.len = 0;
	ft_sdsgrow(&g_editln->str, 64);
	*g_editln->str.buf = '\0';
	g_editln->idx = 0;
	g_editln->row = 0;
	g_editln->rows = 0;
	while ((rd = ft_read(STDIN_FILENO, key, 6)) > 0)
	{
		st = 2;
		bind = g_inskeymap - 1;
		while (st == 2 && (++bind)->rd)
			if (rd == bind->rd && !ft_memcmp(key, bind->key, (size_t)bind->rd))
				st = bind->cb(prompt);
		if (st == 1 || (rd == 1 && rl_editins(prompt, *key) == 1))
			break ;
	}
	if ((*len = g_editln->str.len))
		return (g_editln->str.buf);
	return (NULL);
}
