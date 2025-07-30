#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	printf("%zu\n", sizeof(struct sigaction));
}
