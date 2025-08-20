/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:45 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 15:47:32 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	if (!line)
		return (0);
	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	return (write(2, ERR_OPEN_Q, 43), -1);
}

char	*ft_escaped_line(char *line, int start, int end)
{
	char	*escaped;
	char	*t;
	char	*s;

	if (!line || start < 0 || end < start)
		return (NULL);
	if (end == 0)
		return (ft_strdup(line));
	escaped = ft_esc_str(line + start + 1, ESC_CHARS1, end - start - 2);
	t = ft_strndup(line, start);
	if (!escaped)
		return (NULL);
	s = ft_strjoin(t, escaped);
	if (!s)
		return (NULL);
	free(escaped);
	free(t);
	t = ft_strjoin(s, line + end);
	free(s);
	return (s = NULL, escaped = NULL, t);
}

char	*ft_escape_quotes(char *line)
{
	int		i;
	int		len;
	char	*esc_line;
	char	quote;

	if (!line)
		return (NULL);
	i = 0;
	while (i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			quote = line[i];
			len = ft_quoted_len(line + i, quote);
			if (len <= 0)
				return (NULL);
			esc_line = ft_escaped_line(line, i, i + len);
			free(line);
			line = esc_line;
			i += len;
		}
		i++;
	}
	return (line);
}

char	**ft_tokens(char *line)
{
	char	*s;
	char	**tokens;
	int		i;
	t_cli	*cli;

	if (!line)
		return(NULL);
	s = ft_trim_spaces(line);
	printf("in_trimmed = 8%s8\n", s);
	tokens = ft_token_sep(s);
	cli = ft_init_node(ft_doubleptr_len((void **)tokens));
	free(s);
	if (!tokens)
		return (printf("!tokens\n"), NULL);
	if (!ft_expand_tokens(tokens))
		return (ft_free_d(tokens), NULL);
	i = 0;
	while (i < cli->n_tokens)
	{
		printf("expanded_token[%d] = 8%s8\n", i, tokens[i]);
		i++;
	}
	ft_free_list(&cli);
	return (tokens);
}
