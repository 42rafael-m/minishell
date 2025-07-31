#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// char **s = (char **)ft_calloc(4, sizeof(char *));
	// s[0] = ft_strdup("awk");
	// s[1] = ft_strdup("NR==1");
	// s[2] = ft_strdup("{print 2}");
	// s[3] = NULL;
	// execve("/usr/bin/awk", s, envp);
	int	i = 0;
	char	*s = NULL;
	while (argv[i])
	{
		// printf("argv[i] = %s\n", argv[i]);
		// printf("%d\n", ft_tokenlen(argv[i]));
		char	*t = ft_strjoin(s, argv[i]);
		free(s);
		s = ft_strjoin(t, " ");
		free(t);
		i++;
	}
	// printf("cl = %s\n", s);
	ft_tokens(s);
}
