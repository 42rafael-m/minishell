#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{

	int	i = 0;
	char	*s = NULL;

	while (argv[i])
	{

		char	*t = ft_strjoin(s, argv[i]);
		free(s);
		s = ft_strjoin(t, " ");
		free(t);
		i++;
	}
	printf("s = 8%s8\n", s);
	int n = ft_num_token(s);
	printf("num_token = %d\n", n);
	char	**r = ft_tokens(s);
	free(s);
	i = 0;
	printf("d_len = %d\n", ft_doubleptr_len(r));
	while (i < ft_doubleptr_len(r))
	{
		printf("8%s8\n", r[i]);
		free(r[i]);
		i++;
	}
	free(r[i]);
	free(r);
	// i = 0;
	// char	**x = (char **)ft_calloc(5, sizeof(char *));
	// x[4] = NULL;
	// while (i < 5)
	// {
	// 	x[i] = ft_final_token(r[i], envp);
	// 	if (x[i])
	// 		printf("$%s$\n", x[i]);
	// 	i++;
	// }
}
