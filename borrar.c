#include "minishell.h"

int	main(int argc, char **argv)
{
	int	i = 1;
	char	*s = NULL;
	char	**tokens;
	char	*t;

	while (argv[i])
	{

		t = ft_strjoin(s, argv[i]);
		free(s);
		s = ft_strjoin(t, " ");
		free(t);
		i++;
	}
	tokens = ft_token_space(s);
	i = 0;
	while (tokens[i])
	{
		printf("tokens[%d] = 8%s8\n", i, tokens[i]);
		free(tokens[i++]);
	}
	free(s);
	free(tokens);
}