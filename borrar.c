#include "minishell.h"

int	main(int argc, char **argv)
{
	int	len = ft_quoted_len(argv[1], '\"');
	printf("len = %d\n", ft_strlen(argv[1]));
	printf("%d\n", len);
	printf("%c\n", argv[1][len]);
}