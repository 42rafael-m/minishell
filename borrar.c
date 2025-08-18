#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cli	*cli = ft_init_list();

	printf("argv = 8%s8\n", argv[1]);
	ft_outfile(argv[1], cli);
	printf("outfile = %s\n", cli->outfile);
	ft_free_list(&cli);
}