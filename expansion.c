/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 15:54:58 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delim_len(char *token)
{
	int	i;
	int	len;
	int	token_len;

	if (!token)
		return (0);
	i = 2;
	len = 0;
	token_len = ft_strlen(token);
	while (ft_isspace(token[i]))
		i++;
	while (i < token_len)
	{
		if (token[i] == '\"')
		{
			i++;
			continue ;
		}
		i++;
		len++;
	}
	return (len);
}

char	*ft_trim_delim(char *token, int *option)
{
	int		i;
	int		len;
	int		j;
	char	*delim;
	
	if (!token)
		return (NULL);
	i = 2;
	j = 0;
	len = ft_delim_len(token);
	delim = ft_calloc(len + 1, sizeof(char));
	while (ft_isspace(token[i]))
		i++;
	if (token[i] == '\"')
		*option = 1;
	while (delim && i < ft_strlen(token))
	{
		while (token[i] == '\"')
			i++;
		delim[j++] = token[i++];
	}
	return (delim);
}

int	ft_var_len(char	*var)
{
	int	i;

	if (!var)
		return (0);
	i = 1;
	while (var[i])
	{
		if (ft_strchr(SEP_STR, var[i]) || ft_strchr(NO_VAL_VAR, var[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*ft_expand_var(char	*line, int start, int end)
{
	char	*s;
	char	*t;
	char	*var;

	if (!line)
		return (NULL);
	if (end >= ft_strlen(line))
		return (ft_strndup(line, end));
	var = NULL;
	s = ft_strndup(line + start, end);
	t = ft_strtrim(s, NO_VAL_VAR);
	if (!s || !t)
		return (NULL);
	if (s != t)
		free(s);
	var = getenv(t);
	free(t);
	s = ft_strndup(line, start);
	t = ft_strjoin(s, var);
	free(s);
	s = ft_strjoin(t, line + start + end);
	free(t);
	return (s);
}

char	*ft_expand_line(char *line)
{
	int		i;
	char	*t;

	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'')
			i += (ft_quoted_len(line + i, '\'') + 1);
		if (line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (NULL);
			i += (ft_heredoc_len(line + i));
		}
		if (line[i] == '$' && line[i + 1] && !ft_strchr(NO_VAL_VAR,
				line[i + 1]))
		{
			t = ft_expand_var(line, i, ft_var_len(line + i));
			free(line);
			line = t;
			i += (ft_var_len(line + i) - 1);
		}
		i++;
	}
	return (line);
}
