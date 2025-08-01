#include "minishell.h"

char	**ft_test_quoted_tokens(char *line)
{
	int	i;
	int	len;
	char	**q_tokens;

	i = 0;
	while (i < ft_strlen(line))
	{
		len = ft_quoted_len(line + i);
		printf("q_len = %d\n", len);
		if (len == -1)
			return (q_tokens);
		i += len;
		i++;
	}
	len = ft_num_q_tokens(line);
	printf("q_num = %d\n", len);
	q_tokens = ft_token_quotes(line);
	i = 0;
	while (i < len)
	{
		printf("q_token[i] = 8%s8\n", q_tokens[i]);
		free(q_tokens[i]);
		i++;
	}
	free(q_tokens[i]);
	free(q_tokens);
	return (q_tokens);
}

int	main(int argc, char **argv, char **envp)
{

	int	i = 1;
	char	*s = NULL;
	char	**q_tokens;
	char	*t;

	while (argv[i])
	{

		t = ft_strjoin(s, argv[i]);
		free(s);
		s = ft_strjoin(t, " ");
		free(t);
		i++;
	}
	t = ft_strtrim(s, " ");
	free(s);
	printf("argv = 8%s8\n", t);
	q_tokens = ft_test_quoted_tokens(t);
	// if (ft_strstr(argv[1], "quoted") || ft_strstr(argv[1], "all"))
	// 	q_tokens = ft_test_quoted_tokens(t);
	// else
	// 	q_tokens = ft_token_quotes(t);
	
}
