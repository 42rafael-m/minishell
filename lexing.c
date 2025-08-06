#include "minishell.h"

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	printf("line = %s\n", line);
	if (line[0] == quote)
		i++;
	while (line[i])
	{
		if (line[i] == quote)
		{
			if (line[0] != quote)
				return (i + 2);
			return (i + 1);
		}
		i++;
	}
	return (write(2, ERR_OPEN_Q, 44), -1);
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
	escaped = ft_esc_str(line + start, ESC_CHARS1, end - start);
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
			if (!esc_line)
				return (NULL);
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
	char	*t;
	int i;

	if (!line)
		return(NULL);
	s = ft_trim_spaces(line);
	printf("trim_line = 8%s8\n", s);
	t = ft_expand_line(s);
	printf("exp_line = 8%s8\n", t);
	if (!s || !t)
		return (printf("!s || !t\n"), NULL);
	tokens = ft_token_sep(t);
	if (!tokens)
		return (printf("!tokens\n"), NULL);
	free(t);
	i = 0;
	while (tokens[i])
	{
		tokens[i] = ft_escape_quotes(tokens[i]);
		printf("tokens[%d] = 8%s8\n", i, tokens[i]);
		i++;
	}
	return (tokens);
}