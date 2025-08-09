#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	i = 0;
	int	n;
	while (i < ft_strlen(argv[1]))
	{
		n = ft_quoted_len(argv[1], argv[1][0]);
		printf("q_len = %d\n", n);
		i += n;
	}
}