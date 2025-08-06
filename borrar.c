#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	printf("8%s8\n", argv[1]);
	int	q_len = ft_quoted_len(argv[1], '\"');
	int	len = ft_trim_s_len(argv[1]);
	printf("q_len = %d\n", q_len);
	printf("len = %d\n", len);
	char	*trimmed = ft_trim_spaces(argv[1]);
	printf("trimmed = 8%s8\n", trimmed);
}