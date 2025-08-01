#include "minishell.h"

// char	*ft_get_var(char *var_call, char **envp)
// {
// 	int	i;
// 	int	len;
// 	char	*t;
// 	char	*var;

// 	if (!var_call || !envp)
// 		return (NULL);
// 	i = 0;
// 	var = NULL;
// 	len = ft_strlen(var_call);
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], var_call, len))
// 		{
// 			t = ft_strtrim(envp[i], var_call);
// 			var = ft_strtrim(t, "=");
// 			free(t);
// 			return (var);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*ft_expand_var(char	*token, int start, int end)
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
	var = getenv(t);
	free(t);
	s = ft_strndup(token, start);
	t = ft_strjoin(s, var);
	free(s);
	s = ft_strjoin(t, token + end);
	free(t);
	return (s);
}

char	*ft_expand_token(char *token)
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
				t = ft_expand_var(token, start, i + 1);
			else
				t = ft_expand_var(token, start, i);
			free(token);
			token = t;
			start = INT_MAX;
		}
		i++;
	}
	return (token);
}

char	*ft_final_token(char *token)
{
	char	*escaped;
	char	*trimmed;

	if (!token)
		return (NULL);
	if (token[0] == '\"')
	{
		escaped = ft_esc_char(token, ESC_CHARS2);
		trimmed = ft_strtrim(escaped, "\"");
		free(token);
		free(escaped);
		token = ft_expand_token(trimmed);
		free(trimmed);
		return (token);
	}	
	else if (token[0] == ' ')
	{
		char	*f = NULL;
		trimmed = ft_strtrim(token, " ");
		free(token);
		token = ft_expand_token(trimmed);
		return (token);

	}
	else
	{
		trimmed = ft_strtrim(token, "\'");
		free(token);
		return (trimmed);
	}
	return (token);
}