#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*cl;
	extern int rl_catch_signals;
	extern int rl_catch_sigwinch;
	int	i;

	cl = NULL;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ft_set_sig(PARENT);
	while (1)
	{
		free(cl);
		cl = readline("main: ");
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			printf("sig_recceived\n");

			// rl_redisplay();
		}
		if (!cl)
			return (rl_clear_history(), write(1, "exit\n", 5), 0);
		if (!cl)
			return (free(cl), rl_clear_history(), 2);
		printf("cl = %s\n", cl);
		add_history(cl);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	return (free(cl), rl_clear_history(), 0);
}
