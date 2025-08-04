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

int	ft_sep_len(char *line)
{
	char	redir;
	int		i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strchr(REDIR_S, line[i]))
	{
		redir = line[i++];
		if (line[i] == redir)
			i++;
	}
	while (line[i])
	{
		if (ft_strchr(QUOTES, line[i]))
			i += (ft_quoted_len(line + i, line[i]));
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
		i += len;
		token_num++;
		if (i >= line_len)
			break ;
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
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[len] = NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		len = ft_sep_len(line + i);
		tokens[j++] = ft_strndup(line + i, len);
		i += len;
		if (i >= ft_strlen(line))
			break ;
	}
	return (tokens);
}
