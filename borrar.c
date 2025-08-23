#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{

	int	i;

	char	*trimmed = ft_trim_spaces(argv[1]);
	printf("trimmed = %s\n", trimmed);
	char	**tokens = ft_tokens(trimmed);
	// t_cli	*cli = ft_init_node(ft_doubleptr_len((void **)tokens));
	// int len = ft_sep_len(trimmed);
	// printf("trimmed = %s\n", trimmed);
	free(trimmed);
	// printf("sep_len = %d\n", len);
	// ft_trim_tokens(tokens);
	// t_cli **start = &cli;
	// ft_parse(tokens, cli);
	free(tokens);
}