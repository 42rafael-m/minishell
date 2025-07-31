#include "minishell.h"

char	*ft_get_var(char *var_call, char **envp)
{
	int	i;
	int	len;
	char	*t;
	char	*var;

	if (!var_call || !envp)
		return (NULL);
	printf("var_call = 8%s8\n", var_call);
	i = 0;
	var = NULL;
	len = ft_strlen(var_call);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var_call, len))
		{
			t = ft_strtrim(envp[i], var_call);
			var = ft_strtrim(t, "=");
			free(t);
			printf("var = 8%s8\n", var);
			return (var);
		}
		i++;
	}
	return (NULL);
}

char	*ft_expand_var(char	*token, int start, int end, char **envp)
{
	char	*s;
	char	*t;
	char	*var;

	if (!token)
		return (NULL);
	if (!token[end - 1])
		end--;
	s = ft_strndup(token + start, end);
	t = ft_strtrim(s, NO_VAL_VAR);
	free(s);
	var = ft_get_var(t, envp);
	free(t);
	s = ft_strndup(token, start);
	t = ft_strjoin(s, var);
	free(s);
	free(var);
	s = ft_strjoin(t, token + end);
	free(t);
	printf("expanded_var = 8%s8\n", s);
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
	while (i < ft_strlen(token))
	{
		if (token[i] == '$' && token[i + 1] && token[i + 1] != '?')
			start = i++;
		if (i < ft_strlen(token) && start != INT_MAX && (ft_strchr(NO_VAL_VAR, token[i]) || !token[i + 1]))
		{
			if (!token[i + 1])
				t = ft_expand_var(token, start, i + 1, envp);
			else
				t = ft_expand_var(token, start, i, envp);
			free(token);
			token = t;
			start = INT_MAX;
		}
		i++;
	}
	printf("expanded_token = 8%s8\n", token);
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
		printf("final_token = 8%s8\n", token);
		return (token);
	}	
	else if (token[0] == ' ')
	{
		trimmed = ft_strtrim(token, " ");
		printf("trimmed_spaces = 8%s8\n", trimmed);
		free(token);
		token = ft_expand_token(trimmed, envp);
		free(trimmed);
		printf("final_token = 8%s8\n", token);
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