/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:42 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/18 18:08:56 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_append(char *token, t_cli *cli)
{
	char	*t;
	char	*outfile;
	char	*expanded;

	if (!token || !cli)
		return (0);
	free(cli->outfile);
	t = ft_strtrim(token, "> ");
	if (!t)
		return (0);
	if (t[0] != '\'')
	{
		expanded = ft_expand_line(t);
		cli->outfile = ft_escaped_line(expanded, 0, ft_strlen(expanded));
		if (!cli->outfile)
			return (free(expanded), 0);
		free(expanded);
	}
	else
	{
		cli->outfile = ft_esc_str(t, QUOTES, ft_strlen(t));
		free(t);
		t = ft_strtrim(cli->outfile, "\'");
		free(cli->outfile);
		cli->outfile = t;
	}
	cli->r_mode = APPEND;
	return (1);
}

int	ft_outfile(char *token, t_cli *cli)
{
	char	*t;
	char	*outfile;
	char	*expanded;

	if (!token || !cli)
		return (0);
	free(cli->outfile);
	t = ft_strtrim(token, "> ");
	if (!t)
		return (0);
	if (t[0] != '\'')
	{
		expanded = ft_expand_line(t);
		cli->outfile = ft_escaped_line(expanded, 0, ft_strlen(expanded));
		if (!cli->outfile)
			return (free(expanded), 0);
		free(expanded);
	}
	else
	{
		cli->outfile = ft_esc_str(t, QUOTES, ft_strlen(t));
		free(t);
		t = ft_strtrim(cli->outfile, "\'");
		free(cli->outfile);
		cli->outfile = t;
	}
	return (1);
}

int	ft_infile(char *token, t_cli *cli)
{
	char	*t;
	char	*infile;
	char	*expanded;

	if (!token || !cli)
		return (0);
	free(cli->infile);
	t = ft_strtrim(token, "< ");
	if (!t)
		return (0);
	if (t[0] != '\'')
	{
		expanded = ft_expand_line(t);
		cli->infile = ft_escaped_line(expanded, 0, ft_strlen(expanded));
		if (!cli->infile)
			return (free(expanded), 0);
		free(expanded);
	}
	else
	{
		cli->outfile = ft_esc_str(t, QUOTES, ft_strlen(t));
		free(t);
		t = ft_strtrim(cli->infile, "\'");
		free(cli->infile);
		cli->infile = t;
	}
	return (1);
}

int	ft_args(char *token, t_cli *cli, int pos)
{
	char	**t;

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

	if (!token)
		return (NULL);
	i = 0;
	while (token && token[i])
	{
		printf("t[%d] = 8%s8\n", i, token[i]);
		if (!ft_strncmp(token[i], ">>", 2))
			ft_append(token[i], cli);
		else if (!ft_strncmp(token[i], "<<", 2))
			ft_heredoc(token[i], cli);
		else if (token[i][0] == '<')
			ft_infile(token[i], cli);
		else if (token[i][0] == '>')
			ft_outfile(token[i], cli);
		else if (!cli->cmd)
			ft_cmd(token[i], cli);
		else if (token[i][0] == '|')
		{
			cli->next = ft_init_node();
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