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
		return (NULL);
	file = ft_strtrim(token, ">> ");
	if (!file)
		return (perror("malloc"), 0);
	cli->fdout = open(file, O_APPEND);
	if (cli->fdout == -1)
		return (perror(file), 0);
	return (1);
}

int	ft_herodoc(char *token, t_cli *cli)
{
	char	*delim;

	if (!token || !cli)
		return (NULL);
	delim = ft_strtrim(token, "< ");
	while (delim)
	{
		
	}
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
	cli->delim = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	return (cli);
}

t_cli	*ft_parse(char	**tokens, t_cli *cli)
{
	int		i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens && tokens[i])
	{
		if (!ft_strcmp(tokens[i], ">>", 2))
			ft_append(tokens[i], cli);
		else if (!ft_strncmp(tokens[0], "<<", 2))
			ft_heredoc();
		else if (tokens[i][0] == '<')
			ft_input();
		else if (tokens[i][0] == '>')
			ft_output();
		else if (!cli->cmd)
			ft_cmd();
		else if (tokens[i][0] == '|')
			ft_pipe();
	}
}