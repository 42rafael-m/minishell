#include "minishell.h"

int	ft_check_redir(tokens)
{
	int	i;

	if (!tokens)
		return (0);
	while (tokens[i])
	{
		if (strchr())
	}
}

int	ft_parse_line(char *line. int start, int end)
{
	char	*segment;
	char	**tokens;
	int	i;

	if (!line)
		return (0);
	i = 0;
	segment = ft_strndup(line + start, end);
	tokens = ft_tokens(segment);
	if (!segment || !tokens)
		return (0);
	while (tokens[i])
		tokens[i] = ft_final_token(tokens[i++]);
	i = 0;
	ft_check_redir(tokens);
	return (1);
}

void	ft_init_list(t_cli *cli)
{
	if (!cli)
		return (NULL);
	cli->cmd = NULL;
	cli->cmd_p = NULL;
	cli->args = NULL;
	cli->fdin = 0;
	cli->fdout = 1;
	cli->delim = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
}

t_cli	*ft_parse(char	*line)
{
	t_cli	*cli;
	int	i;
	int	start;
	int	len;

	if (!line)
		return (NULL);
	i = 0;
	start = 0;
	len = ft_strlen(line);
	ft_init_list(cli);
	while (line[i])
	{
		if (line[i] == '|' || i + 1 >= len)
		{
			ft_parse_line(line, star, i);
			start = i + 1;
		}
		i++;
	}
}