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

#include "../minishell.h"

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
	write(2, ERR_OPEN_Q, 43);
	return (-1);
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
	char	*s;

	if (!line)
		return (NULL);
	i = 0;
	s = ft_strdup(line);
	if (ft_strchr(QUOTES, line[0]) && line[1] == line[0])
		return ((char *)ft_calloc(2, 1));
	while (i < ft_strlen(s))
	{
		if (ft_strchr(QUOTES, s[i]))
		{
			if (s[i + 1] == s[i])
				return (free(s), NULL);
			len = ft_quoted_len(s + i,  s[i]);
			if (len <= 0)
				return (free(s), NULL);
			esc_line = ft_escaped_line(s, i, i + len);
			free(s);
			s = esc_line;
			if (s != esc_line)
				free(esc_line);
			i += (len - 3);
		}
		i++;
	}
	return (s);
}

void	ft_free_all(char **token, t_cli **cli)
{
	if (token && cli && *cli)
		ft_free_tokens(token, (*cli)->n_tokens);
	else if (token)
		ft_free_d(token);
}

char	**ft_tokens(char *line, t_shenv *env, t_cli *cli)
{
	int		len;
	char	**tokens;

	if (!line)
		return (NULL);
	if (ft_check_prnts(line))
		return (NULL);
	cli->n_tokens = ft_num_s_tokens(line);
	tokens = ft_token_sep(ft_trim_spaces(line));
	if (!tokens)
		return (NULL);
	tokens = ft_expand_tokens(tokens, &(cli->n_tokens));
	if (!tokens)
		return (ft_free_all(tokens, &cli), NULL);
	if (ft_check_errors(tokens, cli->n_tokens))
		return (ft_free_all(tokens, &cli), NULL);
	len = cli->n_tokens;
	return (tokens);
}
