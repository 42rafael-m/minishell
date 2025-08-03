#include "minishell.h"

char	**ft_trim_tokens(char **tokens)
{
	int	i;
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

int	ft_spacelen(char *line)
{
	int	i;

	if (!line)
		return (0);
	if (ft_strchr(QUOTES, line[0]))
		return (ft_strlen(line));
	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == ' ' && i != 0)
			return (i);
		i++;
	}
	return (i);
}

int	ft_num_s_tokens(char *line)
{
	int	i;
	int	len;
	int	token_num;

	if (!line)
		return (0);
	i = 0;
	token_num = 0;
	while (line[i])
	{
		len = ft_spacelen(line + i);
		i += len;
		token_num++;
		if (i >= ft_strlen(line))
			break ;
	}
	return (token_num);
}

char	**ft_token_space(char *line)
{
	int	i;
	int	j;
	int	len;
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
		len = ft_spacelen(line + i);
		tokens[j++] = ft_strndup(line + i, len);
		i += len;
		if (i >= ft_strlen(line))
			break ;
	}
	return (tokens);
}

char	**ft_insert_s_tokens(char **tokens, int len)
{
	int	i;
	int	j;
	char	**spaced;
	char	**t;

	if (!tokens)
		return (NULL);
	i = 0;
	while (i < ft_doubleptr_len((void **)tokens))
	{
		spaced = ft_token_space(tokens[i]);
		j = ft_doubleptr_len((void **)spaced);
		while (--j >= 0)
		{
			if (spaced[j] && j == (ft_doubleptr_len((void **)spaced) - 1))
				t = (char **)ft_add_re_ptr((void **)tokens, spaced[j], i);
			else if (spaced[j] )
				t = (char **)ft_add_ptr((void **)tokens, spaced[j], i);
			if (t != tokens)
				ft_free_d(tokens);
			if (!t)
				return (NULL);
			tokens = t;
		}
		i += ft_doubleptr_len((void **)spaced);
		ft_free_d(spaced);
	}
	return (tokens);
}
