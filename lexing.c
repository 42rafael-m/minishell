#include "minishell.h"

int	ft_quoted_len(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	if ((line[0] == '\"' || line[0] == '\''))
		i++;
	while (line[i])
	{
		if ((line[i] == '\"' || line[i] == '\''))
		{
			if (line[0] == '\"' || line[0] == '\'')
				return (i + 1);
			return (i);
		}
		if ((line[0] == '\"' || line[0] == '\'') && !line[i + 1])
			return (-1);
		i++;
	}
	return (i);
}

int	ft_num_q_tokens(char *line)
{
	int	i;
	int	len;
	int	token_num;
	char	**tokens;

	if (!line)
		return (0);
	i = 0;
	token_num = 0;
	while (line[i])
	{
		len = ft_quoted_len(line + i);
		if (len == -1)
			return (write(2, ERR_OPEN_Q, 44), -1);
		i += len;
		token_num++;
		if (i >= ft_strlen(line))
			break ;
	}
	return (token_num);
}

char	**ft_token_quotes(char *line)
{
	int	i;
	int	j;
	int	len;
	char	**tokens;

	if (!line)
		return (NULL);
	len = ft_num_q_tokens(line);
	if (len == -1)
		return (NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[len] == NULL;
	i = 0;
	j = 0;
	while (line[i])
	{
		len = ft_quoted_len(line + i);
		tokens[j++] = ft_strndup(line + i, len);
		i += len;
		if (i >= ft_strlen(line))
			break ;
	}
	return (tokens);
}

char	**ft_tokens(char *line)
{
	char	*trimmed;
	char	**spaced;
	char	**tokens;
	int i;

	if (!line)
		return(NULL);
	trimmed = ft_strtrim(line, " ");
	if (!trimmed);
		return (NULL);
	tokens = ft_token_quotes(trimmed);
	tokens = ft_trim_tokens(tokens);
	if (!tokens)
		return (NULL);
	spaced = ft_insert_s_tokens(tokens);
	return (tokens);
}