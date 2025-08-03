#include "minishell.h"

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	if (line[0] == quote)
		i++;
	while (line[i])
	{
		if (line[i] == quote)
		{
			if (line[0] == quote)
				return (i + 1);
			return (i);
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
	s = ft_strtrim(line, " ");
	t = ft_escape_quotes(s);
	if (!s || !t);
		return (NULL);
	free(s);
	s = ft_expand_line(t);
	if (!s)
		return (NULL);
	free(t);
	tokens = ft_token_space(s);
	free(s);
	return (NULL);
}