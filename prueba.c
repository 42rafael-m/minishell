#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**arg;
	char	**x;

	arg = (char **)ft_calloc(5, sizeof(char *));
	arg[0] = ft_strdup("echo -n asdasd");
	arg[1] = ft_strdup("hola");
	arg[2] = ft_strdup("que");
	arg[3] = ft_strdup("tal");
	arg[4] = NULL;
	x = (char **)ft_calloc(3, sizeof(char *));
	x[0] = ft_strdup("echo");
	x[1] = ft_strdup("HOLA");
	x[2] = NULL;
	int n = execve("/usr/bin/echo", arg, envp);
	printf("%d\n",n);
}
