/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:42 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 15:40:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append(char *token, t_cli *cli)
{
	char	*file;

	if (!token || !cli)
		return (0);
	file = ft_strtrim(token, ">> ");
	if (!file)
		return (perror("malloc"), 0);
	cli->fdout = open(file, O_APPEND);
	if (cli->fdout == -1)
		return (perror(file), 0);
	return (1);
}

char	*ft_expand_heredoc(int option, t_cli *cli)
{
	char	*t;

	t = NULL;
	if (option)
	{
		t = ft_expand_line(cli->heredoc);
		if (!t)
			return (NULL);
		cli->heredoc = t;
	}
	return (cli->heredoc);
}

void	ft_here_error(char *delim)
{
	char	*t;
	char	*error_msg;

	if (!delim)
		return ;
	t = ft_strjoin(HERE_ERR, delim);
	error_msg = ft_strjoin(t, "')\n");
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
	free(t);
	return ;
}

int	ft_heredoc(char *token, t_cli *cli)
{
	char	*delim;
	char	*t;
	char	*line;
	int		option;

	if (!token || !cli)
		return (0);
	delim = ft_trim_delim(token, &option);
	if (!delim)
		return (0);
	line = NULL;
	while (1)
	{
		free(line);
		line = NULL;
		line = readline("> ");
		if (!ft_strncmp(line, delim, ft_strlen(line)) || !line)
			break ;
		t = ft_strjoin(cli->heredoc, line);
		free(cli->heredoc);
		cli->heredoc = ft_strjoin(t, "\n");
		free(t);
	}
	if (!line)
		ft_here_error(delim);
	cli->heredoc = ft_expand_heredoc(option, cli);
	return (free(line), free(delim), 1);
}

t_cli	*ft_init_list()
{
	t_cli *cli;

	cli = (t_cli *)ft_calloc(1, sizeof(t_cli));
	if (!cli)
		return (NULL);
	cli->cmd = NULL;
	cli->cmd_p = NULL;
	cli->args = NULL;
	cli->fdin = 0;
	cli->fdout = 1;
	cli->heredoc = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	return (cli);
}

// t_cli	*ft_parse(char	**tokens, t_cli *cli)
// {
// 	int		i;

// 	if (!tokens)
// 		return (NULL);
// 	i = 0;
// 	while (tokens && tokens[i])
// 	{
// 		if (!ft_strcmp(tokens[i], ">>", 2))
// 			ft_append(tokens[i], cli);
// 		else if (!ft_strncmp(tokens[0], "<<", 2))
// 			ft_heredoc();
// 		else if (tokens[i][0] == '<')
// 			ft_input();
// 		else if (tokens[i][0] == '>')
// 			ft_output();
// 		else if (!cli->cmd)
// 			ft_cmd();
// 		else if (tokens[i][0] == '|')
// 			ft_pipe();
// 	}
// }