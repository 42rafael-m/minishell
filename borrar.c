#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd = open(argv[1], O_RDONLY);
	perror("open");
	int	acc = access(argv[1], R_OK);
	printf("fd = %d\n", fd);
	perror("access");
	int	n =  O_CREAT | O_WRONLY | O_TRUNC;
	printf("n = %d\n", n);
}