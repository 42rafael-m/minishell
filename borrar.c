#include "minishell.h"

void	ft_print_node(t_cli *cli)
{
	int	i = 0;

	if (!cli)
		return ;
	printf("cmd = %s\n", cli->cmd);
	printf("infile = %s\n", cli->infile);
	printf("outfile = %s\n", cli->outfile);
	printf("is_builtin = %d\n", cli->is_builtin);
	printf("r_mode = %d\n", cli->r_mode);
	printf("heredoc = %s", cli->heredoc);
	while (cli->args && cli->args[i])
	{
		printf("args[%d] = %s\n", i, cli->args[i]);
		i++;
	}
	i = 0;
	while (cli->env && cli->env[i])
	{
		printf("env[%d] = %s\n", i, cli->env[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cli	*cli = ft_init_node();

	int	i = 0;
	int len = ft_doubleptr_len((void **)argv);
	char	*trimmed = ft_trim_spaces(argv[1]);
	char	**tokens = ft_token_sep(trimmed);
	ft_trim_tokens(tokens);
	while (tokens && tokens[i])
	{
		printf("tokens[%d] = 8%s8\n", i, tokens[i]);
		i++;
	}
	t_cli **start = &cli;
	ft_parse(tokens, cli);
	ft_print_node(cli);
	ft_free_list(start);
	ft_free_d(tokens);
	free(trimmed);
}