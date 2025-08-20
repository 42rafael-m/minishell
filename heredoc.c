/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:19:26 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/18 15:17:08 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("delim = %s\n", delim);
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