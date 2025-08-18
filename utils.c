/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:54 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/18 15:17:33 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_cli **cli)
{
	t_cli		*node;
	t_cli		*next_node;

	if (!cli || !*cli)
		return ;
	node = *cli;
	while (node)
	{
		next_node = node->next;
		free(node->cmd);
		free(node->heredoc);
		free(node->cmd_p);
		free(node->infile);
		free(node->outfile);
		ft_free_d(node->env);
		ft_free_d(node->args);
		free(node);
		node = next_node;
	}
	*cli = NULL;
	return ;
}

int ft_trim_s_len(char *line)
{
	int		i;
	int		len;
	char	sep;

	i = 0;
	len = 0;
	sep = '\0';
	while (line && ft_isspace(line[i]))
		i++;
	while (line && i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			sep = line[i];
			if (ft_quoted_len(line + i, sep)  <= 0)
				return (-1);
			len += ft_quoted_len(line + i, sep);
			i += ft_quoted_len(line + i, sep);
			sep = '\0';
			continue ;
		}
		while (ft_isspace(line[i]) && (( i + 1) >= ft_strlen(line) || ft_isspace(line[i + 1])))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*ft_trim_spaces(char *line)
{
	int		i;
	int		j;
	char	sep;
	char	*trimmed;

	i = 0;
	j = 0;
	sep = '\0';
	if (ft_trim_s_len(line) <= 0)
		return (NULL);
	trimmed = ft_calloc(ft_trim_s_len(line) + 1, sizeof(char));
	while (line && ft_isspace(line[i]))
		i++;
	while (trimmed && line && i < ft_strlen(line))
	{
		while (sep == '\0' && ft_isspace(line[i]) && (ft_isspace(line[i + 1]) || !line[i + 1]))
			i++;
		if (ft_strchr(QUOTES, line[i]))
		{
			if (sep == '\0')
				sep = line[i];
			else if (line[i] == sep)
				sep = '\0';
		}
		trimmed[j++] = line[i++];
	}
	return (trimmed);
}

void	ft_sig_handler(int signal)
{
	struct sigaction	sa;

	g_sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_set_sig(int option)
{
	struct sigaction	sa;

	if (option == 1)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		return ;
	}
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}
