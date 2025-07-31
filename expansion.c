#include "minishell.h"

char	*ft_get_var(char *var_call, char **envp)
{
	int	i;
	int	len;
	char	*t;
	char	*var;

	if (!var_call || !envp)
		return (NULL);
	i = 0;
	var = NULL;
	len = ft_strlen(var_call);
	printf("var_call_len = %s\n", len);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var_call, len))
		{
			t = ft_strtrim(envp[i], var_call);
			var = ft_strtrim(t, "=");
			free(var_call);
			free(t);
			printf("var = %s\n", var);
			return (var);
		}
		i++;
	}
	return (free(var_call), NULL);
}

char	*ft_expand_var(char	*token, int start, int end, char **envp)
{
	char	*s;
	char	*t;
	char	*var;

	if (!token)
		return (NULL);
	var = ft_get_var(ft_strndup(token + start, end), envp);
	s = ft_strndup(token, start);
	t = ft_strjoin(s, var);
	free(s);
	free(var);
	s = ft_strjoin(t, token + end);
	printf("expanded_var = %s\n", s);
	return (s);
}

/* Igual hay que pasar **token en vez de *token */
char	*ft_expand_token(char *token, char **envp)
{
	int	i;
	int	start;
	char	*t;

	i = 0;
	if (!token)
		return (NULL);
	start = INT_MAX;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] != '?')
			start = i;
		if (start != INT_MAX && (ft_strchr(SEP_STR, token[i]) || !token[i + 1]))
		{
			t = ft_expand_var(token, start, i, envp);
			free(token);
			token = t;
			start = 0;
		}
		i++;
	}
	printf("expanded_token = $%s$\n", token);
	return (token);
}

char	*ft_final_token(char *token, char **envp)
{
	char	*escaped;
	char	*trimmed;

	if (!token)
		return (NULL);
	if (token[0] == '\"')
	{
		escaped = ft_esc_char(token);
		trimmed = ft_strtrim(escaped, "\"");
		free(token);
		free(escaped);
		token = ft_expand_token(trimmed, envp);
		free(trimmed);
		printf("final_token = $%s$\n", token);
		return (token);
	}	
	else if (token[0] == ' ')
	{
		trimmed = ft_strtrim(token, " ");
		printf("trimmed_spaces = $%s$\n", trimmed);
		free(token);
		token = ft_expand_token(trimmed, envp);
		free(trimmed);
		printf("final_token = $%s$\n", token);
		return (token);

	}
	else
	{
		trimmed = ft_strtrim(token, "\'");
		free(token);
		printf("final_token = $%s$\n", trimmed);
		return (trimmed);
	}
	printf("final_token = $%s$\n", token);
	return (token);
}