#include "minishell.h"

int	ft_tokenlen(char *cl)
{
	int	i;
	int	len;
	char	sep;

	if (!cl || !cl[0])
		return (0);
	i = 0;
	while (cl[i] == ' '  && ft_strchr(SEP_STR, cl[i + 1]))
		i++;
	len = 0;
	if (cl[i] == ' ' || cl[i] == '\'' || cl[i] == '\"')
		sep = cl[i++];
	else
		sep = ' ';
	while (cl[i])
	{
		if (cl[i] == sep)
			return (len);
		if (sep != ' ' && !cl[i + 1])
			return (-1);
		i++;
		len++;
	}
	return (len);
}

int	ft_num_token(char *cl)
{
	int	i;
	int	len;
	int	token_num;
	char	sep;

	if (!cl)
		return (0);
	i = 0;
	token_num = 0;
	while (cl[i] == ' '  && ft_strchr(SEP_STR, cl[i + 1]))
		i++;
	len = ft_tokenlen(cl + i);
	if (len == 0)
		return (0);
	else
	{
		i += len;
		token_num++;
	}
	while (i < ft_strlen(cl))
	{
		while (cl[i] == ' ' && ft_strchr(SEP_STR, cl[i + 1]))
			i++;
		sep = cl[i];
		len =  ft_tokenlen(cl + i);
		if (len == -1) /* Este error hay que manejarlo bien, asegurarse que se muestra un nuevo prompt */
			return (write(2, "Syntax error: quotes not closed\n", 33), -1);
		if (len > 0)
		{
			token_num++;
			i += len;
		}
		i++;
		if (i <= ft_strlen(cl) && !ft_isspace(cl[i]) && ft_strchr(SEP_STR, cl[i]))
			i++;
	}
	return (token_num);
}

char	**ft_tokens(char *cl)
{
	int	i;
	int	j;
	int	len;
	char	**tokens;

	if (!cl)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_num_token(cl);
	if (len == -1)
		return (NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[len] = NULL;
	while (cl[i] == ' ')
		i++;
	len = ft_tokenlen(cl + i);
	tokens[j++] =  ft_strndup(cl + i, len);
	i += len;
	if(i >= ft_strlen(cl) || ft_tokenlen(cl + i) <= 0)
		return (tokens);
	if (!tokens)
		return(NULL);
	while (i < ft_strlen(cl))
	{
		if (ft_strchr(SEP_STR, cl[i]) && !ft_strchr(SEP_STR, cl[i + 1]))
		{
			len = ft_tokenlen(cl + i);
			tokens[j] = ft_strndup(cl + i, len + 2);
			if (!tokens[j++])
				return (NULL);
			i += len;
		}
		i++;
	}
	return (tokens);
}