#include "minishell.h"

void	ft_signal_h(int signal)
{
	printf("signal = %d\n", signal);
}

int	main(int argc, char **argv)
{
	struct sigaction sa;

	sa.sa_handler = ft_signal_h;
	sigaction(SIGINT, &sa, NULL);
	while (1)
		continue ;
}