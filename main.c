#include "minishell.h"

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	char **s = (char **)ft_calloc(argc + 1, sizeof(char *));
	while (i < argc)
	{
		s[i] = ft_strdup(argv[i]);
		i++;
	}
	s[i] = NULL;
	char **t = ft_lex_pipe(s, &argc);
	i = 0;
	int	len = ft_doubleptr_len((void **)t);
	if (len < argc)
		len = argc;
	while (i <= len)
	{
		if (t && t[i])
			printf("t[%d] = 8%s8\n", i, t[i]);
		i++;
	}
	ft_free_d(t);
}