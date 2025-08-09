/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 15:46:14 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_trim_tokens(char **tokens)
{
	int		i;
	char	*t;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		t = ft_strtrim(tokens[i], " ");
		if (t != tokens[i])
		{
			free(tokens[i]);
			tokens[i] = t;
		}
		i++;
	}
	return (tokens);
}

int	ft_redir_len(char *line)
{
	char	redir;
	int	i;

	i = 0;
	redir = line[i++];
	if (line[i] == redir)
		i++;
	while (ft_isspace(line[i]))
		i++;
	while (line [i])
	{
		if (ft_strchr(REDIR_S, line[i]))
		{
			if (line[i] == '<')
				return (write(2, UNEX_T1, 51), -1);
			return (write(2, UNEX_T2, 51), -1);
		}
		i++;
	}
	return (i);
}

int	ft_sep_len(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strchr(REDIR_S, line[i]))
		return (ft_redir_len(line + i));
	while (i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			printf("q_len = %d\n", ft_quoted_len(line + i, line[i]));
			if (ft_quoted_len(line + i, line[i]) < 0)
				return (-1);
			i = (ft_quoted_len(line + i, line[i]) + i);
			continue ;
		}
		if (ft_strchr(SEP_STR, line[i]) && i != 0)
			return (i);
		i++;
	}
	return (i);
}

int	ft_num_s_tokens(char *line)
{
	int	i;
	int	len;
	int	line_len;
	int	token_num;

	if (!line)
		return (0);
	i = 0;
	token_num = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		len = ft_sep_len(line + i);
		if (len == -1)
			return (printf("sep_len == -1\n"), -1);
		i += len;
		token_num++;
	}
	printf("token_num = %d\n", token_num);
	return (token_num);
}

char	**ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	char	**tokens;

	if (!line)
		return (printf("!line\n"), NULL);
	len = ft_num_s_tokens(line);
	printf("n_tokens = %d\n", len);
	if (len == -1)
		return (NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
	j = 0;
	printf("line_len = %d\n", ft_strlen(line));
	while (tokens && i < ft_strlen(line))
	{
		printf("line[%d] = '%c'\n", i, line[i]);
		while (ft_isspace(line[i]))
			i++;
		printf("sep_len = %d\n", ft_sep_len(line + i));
		if (ft_sep_len(line + i) <= 0)
			return (printf("!sep_len\n"), tokens[len] = NULL, ft_free_d(tokens), NULL);
		tokens[j++] = ft_strndup(line + i, ft_sep_len(line + i) + 1);
		printf("tokens[%d] = 8%s8\n", j - 1, tokens[j - 1]);
		printf("len = %d\n", ft_sep_len(line + i));
		i += ft_sep_len(line + i);
		printf("i = %d\n", i);
	}
	return (tokens[len] = NULL, tokens);
}
