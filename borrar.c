#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{

	int	n;
	int	op;
	t_cli	*cli;

	cli = ft_init_list();
	op = 0;
	n = ft_delim_len(argv[1]);
	printf("here_len = %d\n", n);
	char	*s = ft_trim_delim(argv[1], &op);
	printf("delim = 8%s8, op = %d\n", s, op);
	ft_heredoc(argv[1], cli);
	printf("heredoc = 8%s8\n", cli->heredoc);
	ft_free_list(&cli);
	free(s);
}