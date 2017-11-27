/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:39:49 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh/eval.h"

static inline t_ret	msh_eval_word(t_msh *self, t_tok *tok)
{
	t_vstr		av;
	t_ret		ret;
	t_dstr		*ident;
	char		exe[4096];
	t_cmd		bi;

	if ((bi = msh_bi(ft_tok_ident(tok)->buf)))
	{
		if (msh_exe_av(self, &av, ft_tok_ident(tok)->buf) == RET_ERR)
			return (RET_ERR);
		return (ft_dtor(((*bi)(self, &av)), (t_dtor)ft_vstr_dtor, &av, NULL));
	}
	ident = ft_tok_ident(tok);
	if ((ret = msh_exe_lookup(self, ident->buf, S_IFREG | S_IXUSR, exe)) != 0)
	{
		if ((ret = (ret != RET_ERR ? msh_exe_av(self, NULL, NULL) : ret)) != -1)
			(void)(ft_puts(2, "msh: Command not found: '") &
				ft_puts(2, ident->buf) & ft_putl(2, "'"));
		return (ret == RET_ERR ? ret : RET_NOK);
	}
	if (msh_exe_av(self, &av, exe) == RET_ERR)
		return (RET_ERR);
	ret = msh_exe_run(self, &av);
	ft_vstr_dtor(&av, NULL);
	return (ret);
}

inline t_ret		msh_eval(t_msh *self, t_tok *tok)
{
	char	buf[4096];

	if (tok->id == MSH_TOK_WORD)
		return (msh_eval_word(self, tok));
	else
	{
		ft_puts(2, "unexpected token '");
		buf[ft_intstr(buf, tok->id, 10)] = 0;
		ft_puts(2, buf);
		if (ft_isprint(tok->id) && ft_putl(2, "', '"))
			ft_putc(2, tok->id);
		ft_putl(2, "'");
	}
	return (RET_NOK);
}
