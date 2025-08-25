/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:42 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/21 17:13:38 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = APPEND;
	while (token[i] == '>' && i < 2)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (0);
	return (1);
}

int	ft_outfile(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = 0;
	while (token[i] == '>' && i < 1)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (0);
	return (1);
}

int	ft_infile(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->infile);
	free(cli->heredoc);
	cli->heredoc = NULL;
	while (token[i] == '<' && i < 1)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]))
		cli->infile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->infile = ft_strdup(token + i);
	if (!cli->infile)
		return (0);
	return (1);
}

int	ft_args(char *token, t_cli *cli, int pos)
{
	char	**t;

	if (!token)
		return (0);
	if (!cli->args)
	{
		cli->args = (char **)ft_calloc(2, sizeof(char *));
		if (!cli->args)
			return (perror("malloc"), 0);
		cli->args[1] = NULL;
		cli->args[0] = ft_strdup(token);
		if (!cli->args[0])
			return (perror("malloc"), 0);
	}
	else
	{
		t = (char **)ft_add_ptr((void *)cli->args, (char *)token, pos);
		if (!t)
			return (perror("malloc"), 0);
		ft_free_d(cli->args);
		cli->args = t;
	}
	return (1);
}

t_cli	*ft_parse(char	**token, t_cli *cli)
{
	int		i;

	if (!token || !cli)
		return (NULL);
	i = 0;
	while (i <= cli->n_tokens)
	{
		if (token[i] && !ft_strncmp(token[i], ">>", 2))
			ft_append(token[i], cli);
		else if (token[i] && !ft_strncmp(token[i], "<<", 2))
		{
			if (ft_heredoc(token[i], cli) < 0);
				return (NULL);
		}
		else if (token[i] && token[i][0] == '<')
			ft_infile(token[i], cli);
		else if (token[i] && token[i][0] == '>')
			ft_outfile(token[i], cli);
		else if (token[i] && !cli->cmd)
			ft_cmd(token[i], cli);
		else if (token[i] && token[i][0] == '|')
		{
			// if (i > 0 && token[i - 1][0] == '|')
			// 	return (write(2, PIPE_ERR, 50), NULL);
			cli->next = ft_init_node(cli->n_tokens, cli->env);
			if (!cli->next)
				return (NULL);
			cli = cli->next;
		}
		else
			ft_args(token[i], cli, ft_doubleptr_len((void **)cli->args));
		i++;
	}
	return (cli);
}