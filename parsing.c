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

int	ft_parse_line(char *line, int start, int end)
{
	char	**tokens;
	int		i;

	if (!line)
		return (0);
	i = 0;
	tokens = ft_tokens(line);
	if (!tokens)
		return (0);

	return (1);
}

void	ft_init_list(t_cli *cli)
{
	if (!cli)
		return ;
	cli->cmd = NULL;
	cli->cmd_p = NULL;
	cli->args = NULL;
	cli->fdin = 0;
	cli->fdout = 1;
	cli->delim = NULL;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	return ;
}

// t_cli	*ft_parse(char	**tokens)
// {
// 	t_cli	*cli;
// 	int		i;

// 	if (!tokens)
// 		return (NULL);
// 	ft_init_list(cli);
// 	while (tokens && tokens[i])
// 	{
// 		if (!ft_strncmp(tokens[0], ">>", 2))
// 			ft_append();
// 		else if (!ft_strncmp(tokens[0], "<<", 2))
// 			ft_heredoc();
// 		else if (tokens[i][0] == '<')
// 			ft_input();
// 		else if (tokens[i][0] == '>')
// 			ft_output();
// 		else if (!cli->cmd)
// 			ft_cmd();
// 		else if (tokens[i][0] == '|')
			
// 	}
// }