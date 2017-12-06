/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/exe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/06 19:06:55 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXE_H
# define LIBFT_EXE_H

# include "lib.h"
# include "ds.h"
# include "io.h"
# include "fs.h"

typedef enum 	e_job_kind
{
	JOB_EXE = 0,
	JOB_FN
}				t_job_kind;

typedef enum	e_job_op
{
	JOB_OP_NONE = 0,
	JOB_OP_OR,
	JOB_OP_AND,
	JOB_OP_PIPE,
	JOB_OP_RIN,
	JOB_OP_ROUT,
	JOB_OP_RAIN,
	JOB_OP_RAOUT
}				t_job_op;

struct			s_job;

typedef int		(*t_job_fn)(void *data, int ac, char **av, char **env);
typedef void	(*t_job_cb)(struct s_job *job);

typedef struct	s_job
{
	t_job_kind	kind;
	t_job_op	op;
	char		**av;
	char		**env;
	pid_t		pid;
	t_job_fn	fn;
	t_job_cb	cb;
	int			st;
	void		*data;
	char		*out;
	char		*in;
}				t_job;

typedef t_vec	t_worker;

extern t_st		ft_job_exe(t_job *self, char *path, char **av, char **env);
extern void		ft_job_fn(t_job *self, t_job_fn fn, char **av, char **env);
extern void		ft_job_output(t_job *self, char *str);
extern void		ft_job_cb(t_job *self, t_job_cb cb);
extern void		ft_job_data(t_job *self, void *data);
extern void		ft_job_operate(t_job *self, t_job_op op);
extern void		ft_job_free_data(t_job *self);
extern void		ft_job_dtor(t_job *self);
extern t_st		ft_job_run(t_job *self, int *wr, int *rd);

extern void		ft_worker_ctor(t_worker *jobs);
extern void		ft_worker_dtor(t_worker *self);
extern t_job	*ft_worker_push(t_worker *self, t_job *job);
extern	t_st	ft_worker_join(t_worker *self);
extern t_st		ft_worker_run(t_worker *self);
extern void		ft_worker_clear(t_worker *self);

#endif
