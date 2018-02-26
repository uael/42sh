/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_FUNC_H
# define USH_FUNC_H

# include <libft.h>

struct s_fn;

typedef struct	s_fn
{
	char const	*ln;
	t_deq		body;
	struct s_fn	*next;
}				t_func;

extern void		sh_funcdtor(void);
extern void		sh_funcset(char const *name, t_deq *body, char const *ln);
extern t_func	*sh_funcget(char const *name);

#endif
