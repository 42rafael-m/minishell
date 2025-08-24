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

char	**ft_lex_pipe(char **token, int *len)
{
	char	**t;
	char	**s;
	int		spaces;
	int		i;

	if (!token || !len || *len <= 0)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '|' && token[i][1])
		{
			spaces = 1;
			t = (char **)ft_add_re_ptr((void **)token, "|", i);
			while (ft_isspace(token[i][spaces]))
				spaces++;
			s = (char **)ft_add_ptr((void **)t, token[i] + spaces, i + 1);
			if (!t || ! s)
				return (ft_free_d(s), ft_free_d(t), NULL);
			ft_free_tokens(token, *len);
			ft_free_tokens(t, *len);
			token = s;
			*len++;
		}
		i++;
	}
	return (token);
}

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

t_cli	*ft_tokens(char *line, char **env)
{
	char	*s;
	char	**tokens;
	int		len;
	t_cli	*cli;

	if (!line)
		return(NULL);
	s = ft_trim_spaces(line);
	tokens = ft_token_sep(s);
	len = ft_num_s_tokens(s);
	free(s);
	cli = ft_init_node(len, ft_load_env(env));
	if (!tokens || !cli)
		return (printf("!tokens\n"), ft_free_tokens(tokens, ft_doubleptr_len((void **)tokens)), ft_free_list(&cli), NULL);
	tokens = ft_expand_tokens(tokens, &(cli->n_tokens));
	if (!tokens)
		return (ft_free_tokens(tokens, cli->n_tokens), NULL);
	ft_parse(tokens, cli);
	ft_free_tokens(tokens, cli->n_tokens);
	return (cli);
}
