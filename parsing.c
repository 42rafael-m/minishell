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

// int	ft_append(char *token, t_cli *cli)
// {
// 	char	*t;
// 	char	*outfile;

// 	if (!token || !cli)
// 		return (0);
// 	t = ft_strtrim(token, " >");
// 	if (!t)
// 		return (0);
// 	if (ft_strchr(QUOTES, t[0]))
// 	{
// 		cli->outfile = ft_strndup(cli + 1, (ft_strlen(t) - 2));
// 		if (!cli->outfile)
// 			return (free(t), NULL);
// 		free(t);
// 	}
// 	else
// 		cli->outfile = t;
// 	return (1);
// }

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
		printf("expanded = %s\n", expanded);
		cli->outfile = ft_escaped_line(expanded, 0, ft_strlen(expanded));
		if (!cli->outfile)
			return (free(expanded), 0);
		free(expanded);
	}
	else
		cli->outfile = expanded;
	printf("outfile = 8%s8\n", cli->outfile);
	return (1);
}

int	ft_infile(char *token, t_cli *cli)
{
	char	*t;

	if (!token || !cli)
		return (0);
	t = ft_strtrim(token, "< ");
	if (!t)
		return (0);
	cli->infile = t;
	return (1);
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
	cli->infile = NULL;
	cli->outfile = NULL;
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