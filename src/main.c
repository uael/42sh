#include <libft.h>

int main(int ac, char **av, char **env)
{
	char	*l;
	t_term	term;

	(void)ac;
	(void)av;
	if (ft_term_ctor(&term, env, "/Users/alucas-/.21shry"))
		return (EXIT_FAILURE);
	while ((l = ft_readline(&term, "$> ")))
	{
		ft_putf(1, l);
		if (ft_strcmp("exit\n", l) == 0)
			break ;
	}
	ft_term_dtor(&term);
	return (EXIT_SUCCESS);
}
