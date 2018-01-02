/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit/move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:23:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/edit.h"

inline void	sh_editleft(t_editln *ln, char const *prompt)
{
	if (ln->idx)
	{
		--ln->idx;
		sh_editprint(ln, prompt);
	}
}

inline void	sh_editright(t_editln *ln, char const *prompt)
{
	if (ln->idx != ln->len)
	{
		++ln->idx;
		sh_editprint(ln, prompt);
	}
}

inline void	sh_edithome(t_editln *ln, char const *prompt)
{
	if (ln->idx)
	{
		ln->idx = 0;
		sh_editprint(ln, prompt);
	}
}

inline void	sh_editend(t_editln *ln, char const *prompt)
{
	if (ln->idx != ln->len)
	{
		ln->idx = ln->len;
		sh_editprint(ln, prompt);
	}
}
