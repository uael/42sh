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

#include "msh/edit.h"

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

/*static t_editbind	g_inskeymap[] =
{
	{1, K_RETURN, NULL},
	{1, K_ENTER, NULL},
	{1, K_BACKSPACE, NULL},
	{1, K_CTRL_A, NULL},
	{1, K_CTRL_B, NULL},
	{1, K_CTRL_D, NULL},
	{1, K_CTRL_E, NULL},
	{1, K_CTRL_F, NULL},
	{1, K_CTRL_H, NULL},
	{1, K_TAB, NULL},
	{1, K_CTRL_P, NULL},
	{1, K_CTRL_R, NULL},
	{1, K_CTRL_T, NULL},
	{1, K_CTRL_U, NULL},
	{3, K_LEFT, sh_editleft},
	{3, K_RGT, sh_editright},
	{3, K_UP, NULL},
	{3, K_DOWN, NULL},
	{3, K_HOME, sh_edithome},
	{3, K_END, sh_editend},
	{4, K_DELETE, NULL},
	{6, K_CTRL_UP, NULL},
	{6, K_CTRL_DOWN, NULL},
	{6, K_CTRL_RIGHT, NULL},
	{6, K_CTRL_LEFT, NULL},
	{0, NULL, NULL},
};*/

extern int		sh_editln(t_editln *ln, char const *prompt, size_t plen)
{
	ssize_t		rd;
	char		key[6];


	(void)prompt;
	(void)plen;
	while ((rd = ft_read(STDIN_FILENO, key, 6)) > 0)
	{
		if (rd == 3 && !ft_memcpy(key, K_LEFT, 3))
			sh_editleft(ln, prompt);
		else if (rd == 3 && !ft_memcpy(key, K_RGT, 3))
			sh_editright(ln, prompt);
		else if (rd == 3 && !ft_memcpy(key, K_HOME, 3))
			sh_edithome(ln, prompt);
		else if (rd == 3 && !ft_memcpy(key, K_END, 3))
			sh_editend(ln, prompt);
		else if (rd == 1)
		{
			if (!ft_memcmp(key, "\xa", 1) || !ft_memcmp(key, "\xd", 1))
				*key = '\n';
			if (*key == '\n' || (!ft_iscntrl(*key) && ft_isascii(*key)))
			{
				if (ln->len != ln->idx)
					ft_memmove(ln->buf + ln->idx + 1, ln->buf + ln->idx,
						ln->len - ln->idx);
				ln->buf[ln->idx] = *key;
				ln->buf[++ln->len] = '\0';
				++ln->idx;
				if (*key == '\n')
				{
					ft_write(STDOUT_FILENO, "\n", 1);
					break ;
				}
				sh_editprint(ln, prompt);
			}
		}
	}
	return (YEP);
}
