#include "libft/libft.h"

void	ft_echo(char *line, int option)
{
	char	*s;

	s = ft_trim_spaces(line);
	write(1, s, ft_strlen(s));
	if (!option)
		write(1, "\n", 1);
	return ;
}

int	ft_built_ins(char *line)
{
	char *s;

	if (ft_strstrcd(line, "echo")) 
}

int	main()
{
	ft_echo("hola que tal", 1);
}