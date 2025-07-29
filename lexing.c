#include "minishell.h"

size_t	ft_spacelen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != ' '))
		i++;
	return (i);
}

int	ft_spaces(char *str)
{
	int	i;
	int	space;
	int	block;

	i = 0;
	space = 0;
	block = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == 123 || str[i] == 34 || str[i] == 39)
			block = 1;
		if (str[i] == 125 || str[i] == 34 || str[i] == 39)
			block = 0;
		if (str[i] == 32 && !block)
			space++;
		i++;
	}
	return (space);
}

char	*ft_load_line(char *cmd, int start, size_t len)
{
	char	*t;
	char	*argv;

	if (!cmd)
		return (NULL);
	if (cmd[0] == 34)
		argv = ft_esc_char(cmd);
	else
		argv = ft_substr(cmd, start, len);
	if (!argv)
		return (NULL);
	if (ft_strchr(argv, '\'') || ft_strchr(argv, '"'))
	{
		t = argv;
		argv = ft_strtrim(t, "\"' ");
		free (t);
		if (!argv)
			return (NULL);
	}
	return (argv);
}

char	**ft_load_argv(char **argv, char *cmd)
{
	int	j;
	int	block;
	int	start;
	int	i;

	i = 0;
	j = 1;
	start = 0;
	while (cmd[i])
	{
		if (block && (cmd[i] == 34 || cmd[i] == 39))
			block = 0;
		if (!block && (cmd[i] == 34 || cmd[i] == 39))
			block = 1;
		if ((cmd[i] == ' ' && !block) || !cmd[i + 1])
		{
			argv[j] = ft_load_line(cmd, start, i);
			if (!argv[j])
				return (ft_free_d(argv), NULL);
			start = i + 1;
			j++;
		}
		i++;
	}
	return (argv[i] = NULL, argv);
}

char	**ft_argv(char *cmd)
{
	char	**argv;
	int		space;
	int		i;

	if (!cmd)
		return (NULL);
	i = ft_spacelen(cmd) + 1;
	if (i < 0)
		return (NULL);
	space = ft_spaces(cmd);
	if (!ft_strchr(cmd, 34) && !ft_strchr(cmd, 39) && !ft_strchr(cmd, 123))
		return (ft_split(cmd, ' '));
	argv = (char **)ft_calloc(space + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_substr(cmd, 0, ft_spacelen(cmd));
	if (!argv[0])
		return (NULL);
	argv = ft_load_argv(argv, cmd + i);
	return (argv);
}