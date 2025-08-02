#include "minishell.h"

int	main(int argc, char **argv)
{
	char	**r;

	printf("HOLA\n");
	r = (char **)ft_add_re_ptr((void **)argv, "hola", 1);
	int i = 0;
	int	len = ft_doubleptr_len((void **)r);
	printf("len = %d\n", len);
	while (r && r[i])
	{
		printf("%s\n", r[i]);
		i++;
	}
	ft_free_d(r);
}