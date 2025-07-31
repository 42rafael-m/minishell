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
	printf("%s\n", cl + i);
	printf("len = %d\n", len);
	if (len == 0)
		return (0);
	else
	{
		i += len;
		token_num++;
	}
	while (cl[i])
	{
		while (cl[i] == ' ' && ft_strchr(SEP_STR, cl[i + 1]))
			i++;
		sep = cl[i];
		len =  ft_tokenlen(cl + i);
		if (len == -1) /* Este error hay que manejarlo bien, asegurarse que se muestra un nuevo prompt */
			return (write(2, "Syntax error: quotes not closed\n", 33), -1);
		if (/*(cl[i] == ' ' || cl[i] == '\'' || cl[i] == '\"') && */len > 0)
		{
			token_num++;
			i += len;
		}
		i++;
		if (!ft_isspace(cl[i]) && ft_strchr(SEP_STR, cl[i]))
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
	tokens = (char **)ft_calloc(ft_num_token(cl), sizeof(char *));
	if (!tokens)
		return (NULL);
	while (cl[i] == ' ')
		i++;
	len = ft_tokenlen(cl + i);
	tokens[j++] =  ft_strndup(cl + i, len);
	i += len;
	if (!tokens)
		return(NULL); /* igual no hay que hacer esta comprobación, o mantener j para añadir el siguiente token en esta posición */
	while (cl[i])
	{
		/* Mirar si sustituir ' ' por ft_isspace en todas las funciones, también es posible que valga la pena un macro con ' ', \t, \n, ", '... */
		if (ft_strchr(SEP_STR, cl[i]) && !ft_strchr(SEP_STR, cl[i + 1]))
		{
			len = ft_tokenlen(cl + i);
			tokens[j] = ft_strndup(cl + i + 1, len);
			if (!tokens[j++])
				return (NULL); /* Manejar igual que el error de antes */
			i += len;
		}
		i++;
	}
	return (tokens[j] = NULL, tokens);
}