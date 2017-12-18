#include <librl.h>
#include <alloca.h>

int main(void)
{
	t_rl	*rl;
	char	*line;

	rl = alloca(sizeof(t_rl));
	if (rl_ctor(rl, STDIN_FILENO, STDOUT_FILENO, 1))
		return (THROW(WUT));
	while ((line = rl_readline(rl, "$> ")))
		ft_putf(1, "line: '%s'\n", line);
	return (0);
}
