/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/18 17:31:12 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim_delim(char *token, int *option)
{
	char	*delim;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
	while (token[i] == '<' && i < 2)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]))
	{
		if (token[i] == '\"')
			*option = 1;
		delim = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	}
	else
		delim = ft_strdup(token + i);
	return (delim);
}

int	ft_var_len(char	*var)
{
	int	i;
	int	len;

	if (!var)
		return (0);
	i = 1;
	len = ft_strlen(var);
	while (i < len)
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
	if (end > ft_strlen(line))
		return (ft_strndup(line, end));
	var = NULL;
	s = ft_strndup(line + start, end);
	t = ft_strtrim(s, NO_VAL_VAR);
	if (!s || !t)
		return (free(s), free(t), NULL);
	free(s);
	var = getenv(t);
	free(t);
	s = ft_strndup(line, start);
	t = ft_strjoin(s, var);
	free(s);
	s = NULL;
	s = ft_strjoin(t, line + start + end);
	free(t);
	t = NULL;
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
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
		}
		if (line[i] == '$' && line[i + 1] && !ft_strchr(NO_VAL_VAR,
				line[i + 1]))
		{
			t = ft_expand_var(line, i, ft_var_len(line + i));
			if (line != t)
				free(line);
			line = t;
		}
		i++;
	}
	t = ft_strtrim(line, " ");
	return (free(line), line = NULL, t);
}

int	ft_expand_tokens(char **tokens)
{
	char	*t;
	int		i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
	{
		t = ft_expand_line(tokens[i]);
		printf("in_expanded = 8%s8\n", t);
		tokens[i] = ft_escape_quotes(t);
		free(t);
		printf("in_escaped = 8%s8\n", tokens[i]);
		// if (t && !tokens[i])
		// 	return (0);    Comentado por caso de que el token sea "", que devuelve nulo y no hay error. Mirar cómo manejar los otros errores
		i++;
	}
	return (1);
}