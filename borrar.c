#include "minishell.h"

int	main(int argc, char **argv)
{
	char	**r;

	r = (char **)ft_add_ptr((void **)argv, "hola", 1);
	int i = 0;
	int	len = ft_doubleptr_len((void **)r);
	printf("len = %d\n", len);
	while (r && *r)
	{
		printf("%s\n", *r);
		r++;
	}
}