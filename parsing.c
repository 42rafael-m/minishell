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

t_cli	*ft_init_node()
{
	t_cli *cli;

	cli = (t_cli *)ft_calloc(1, sizeof(t_cli));
	if (!cli)
		return (NULL);
	cli->cmd = NULL;
	cli->args = NULL;
	cli->env = NULL;
	cli->infile = NULL;
	cli->outfile = NULL;
	cli->heredoc = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	return (cli);
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
		if (!ft_strncmp(token[i], ">>", 2) && !ft_append(token[i], cli))
			return (NULL);
		else if (!ft_strncmp(token[0], "<<", 2) && !ft_heredoc(token[i], cli))
			return (NULL);
		else if (token[i][0] == '<' && !ft_infile(token[i], cli))
			return (NULL);
		else if (token[i][0] == '>' && !ft_outfile(token[i], cli))
			return (NULL);
		else if (!cli->cmd && !ft_cmd(token[i], cli))
			return (NULL);
		else if (token[i][0] == '|')
		{
			cli->next = ft_init_node();
			if (!cli->next)
				return (NULL);
			cli = cli->next;
		}
		else
		{
			printf("HOLA\n");
			cli->args = (char **)ft_add_ptr((void *)cli->args, (char *)token[i], i + 1);
			if (!cli->args)
				return (NULL);
		}
		i++;
	}
	return (cli);
}