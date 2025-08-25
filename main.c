#include "minishell.h"

void ft_sig_h(int signal)
{
	int	status;

	status = 0;
	if (signal == SIGINT)
		write(1, "Hello!\n", 7);
	exit(status);
}

int	main(int argc, char **argv)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ft_sig_h;
	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa, NULL);
	while (1)
		continue ;
}