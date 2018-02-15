/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ush/vm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USH_VM_H
# define USH_VM_H

# include <libft.h>
# include <ush.h>

# define OP_MAX UINT16_MAX
# define OP_LOCK (1 << 1)

enum e_op
{
	OP_BIN = 0,
	OP_ARG = 0,
	OP_REDIR,
	OP_IF,
	OP_ELIF,
	OP_ELSE,
	OP_FI,
	OP_TERM
};

typedef struct	s_op
{
	uint16_t	pos;
	uint16_t	len;
	uint16_t	jump;
	uint8_t		kind;
	uint8_t		flags;
}				t_op;

typedef int		(t_opc)(t_op *op, t_vec *av, t_vec *env, char *ln);

static t_op		g_ops[OP_MAX];

int				vm_evalbin(t_op *op, t_vec *av, t_vec *env, char *ln);

static int		vm_eval(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	static const t_opc	*opc[OP_TERM + 1] = {
		[OP_BIN] = vm_evalbin
	};
	return (opc[op->kind](op, av, env, ln));
}

static int		vm_evalbin(t_op *op, t_vec *av, t_vec *env, char *ln)
{
	av->len = 0;
	while (!av->len)
	{
		if (!(op->flags & OP_LOCK))
		{
			sh_wordexplode(av, ln + op->pos, op->len);
			if (!av->len && ++op->kind != OP_ARG)
				return (vm_eval(op, av, env, ln));
		}
		else
			*(char **)ft_vecpush(av) = ft_strndup(ln + op++->pos, op->len);
	}
	return (vm_eval(++op, av, env, ln));
}

#endif
