#include "libft/libft.h"

void	ft_echo(char *line, int option)
{
	char	*s;

	s = ft_trim_spaces(line);
	write(1, s, ft_stren(s));
	if (!option)
		write(1, "\n", 1);
	return ;
}