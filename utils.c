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

void	ft_print_list(t_cli *cli)
{
	int	i = 0;
	int	node = 0;

	while (cli)
	{
		if (!cli)
			return ;
		if (cli->cmd)
			printf("cmd %d = %s\n", node, cli->cmd);
		if (cli->infile)
			printf("infile %d = %s\n", node, cli->infile);
		if (cli->outfile)
			printf("outfile %d = %s\n", node, cli->outfile);
		if (cli->is_builtin)
			printf("is_builtin %d = %d\n", node, cli->is_builtin);
		if (cli->r_mode)
			printf("r_mode %d = %d\n", node, cli->r_mode);
		if (cli->heredoc)
			printf("heredoc %d = %s\n", node, cli->heredoc);
		while (cli->args && cli->args[i])
		{
			printf("args[%d] %d = %s\n", i, node, cli->args[i]);
			i++;
		}
		i = 0;
		while (cli->env && cli->env[i])
		{
			printf("env[%d] %d = %s\n", i, node, cli->env[i]);
			i++;
		}
		cli = cli->next;
		node++;
	}
}

void	ft_free_tokens(char **tokens, int n)
{
	int	i;

	i = 0;
	while (tokens && i <= n)
	{
		free(tokens[i]);
		i++;
	}
	if (tokens)
		free(tokens);
}

t_cli	*ft_init_node(int len)
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
	cli->n_tokens = len;
	return (cli);
}

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
		node->cmd = NULL;
		free(node->heredoc);
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
