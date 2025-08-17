#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cli	*cli = ft_init_list();

	ft_outfile(argv[1], cli);
	printf("outfile = %s\n", cli->outfile);
	ft_free_list(&cli);
}