/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/13 08:28:05 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>

#define SNS(S) (S), sizeof(S) - 1
#define OK ft_write(STDOUT_FILENO, SNS("\033[32m[✔]\033[0m\n"))
#define NOK ft_putf(1,"\033[31m[✖]\033[0m %s:%d\n",__FILE__,__LINE__)
#define ASSERT(E) if(!(E)){NOK;return(NOP);}

typedef int		(t_test_cb)(void);

typedef struct	s_test
{
	char const	*name;
	t_test_cb	*cb;
}				t_test;

extern t_test	g_tests[];

extern int		setup(void);
extern int		teardown(void);
