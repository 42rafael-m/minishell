/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/18 17:44:27 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_trim_tokens(char **tokens)
{
	int		i;
	char	*t;

	i = 0;
	while (tokens && tokens[i])
	{
		t = ft_strtrim(tokens[i], " \t");
		if (!t)
			return (perror("malloc"), NULL);
		free(tokens[i]);
		tokens[i++] = t;
	}
	return (tokens);
}

int	ft_heredoc_len(char *line)
{
	char	redir;
	int		i;
	int		len;
	
	i = 0;
	while (ft_strchr(REDIR_S, line[i]) && i < 2)
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_strchr(REDIR_S, line[i]))
		return (write(2, UNEX_T1, 50), -1);
	if (ft_strchr(QUOTES, line[i]))
	{
		printf("line[%d] = %c\n", i, line[i]);
		len = ft_quoted_len(line + i, line[i]);
		if (len < 0)
			return (printf("here_len error\n"), -1);
		i += len;
	}
	while (line [i])
	{		
		if (ft_strchr(SEP_STR, line [i]))
			return (printf("heredoc_len = %d\n", i), i);
		i++;
	}
	return (printf("heredoc_len = %d\n", i), i);
}

int	ft_sep_len(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (i < ft_strlen(line) && ft_isspace(line[i]))
		i++;
	if (ft_strchr(REDIR_S, line[i]))
		return (ft_heredoc_len(line + i));
	while (i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			if (ft_quoted_len(line + i, line[i]) < 0)
				return (printf("sep_len error\n"), -1);
			i = (ft_quoted_len(line + i, line[i]) + i);
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
		printf("sep = %c\n", line[i + len]);
		if (len == -1)
			return (-1);
		i += len;
		token_num++;
	}
	return (token_num);
}

char	**ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	char	**tokens;

	if (!line)
		return (NULL);
	len = ft_num_s_tokens(line);
	if (len == -1)
		return (NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (tokens && i < ft_strlen(line))
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_sep_len(line + i) <= 0)
			return (tokens[len] = NULL, ft_free_d(tokens), NULL);
		tokens[j++] = ft_strndup(line + i, ft_sep_len(line + i));
		i += ft_sep_len(line + i);
	}
	return (tokens[len] = NULL, tokens);
}
