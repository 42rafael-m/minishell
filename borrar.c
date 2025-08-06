#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cli	*cli;
	int	i;
	cli = ft_init_list();
	cli->env = ft_load_env(envp);
	i = 0;
	while (cli->env[i])
		printf("%s\n", cli->env[i++]);
}