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

char	*ft_expand_var(char	*line, int start, int end)
{
	char	*s;
	char	*t;
	char	*var;

	if (!line)
		return (NULL);
	if (!line[end - 1])
		end--;
	s = ft_strndup(line + start, end);
	t = ft_strtrim(s, NO_VAL_VAR);
	free(s);
	var = getenv(t);
	free(t);
	s = ft_strndup(line, start);
	t = ft_strjoin(s, var);
	free(s);
	s = ft_strjoin(t, line + end);
	free(t);
	return (s);
}

char	*ft_expand_line(char *line)
{
	int	i;
	char	*t;

	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'')
			i += (ft_quoted_len(line + i, '\'') + 1);
		if (i < ft_strlen(line) && line[i] == '$' && (i + 1 > ft_strlen(line) || ft_strchr(NO_VAL_VAR, line[i + 1])))
		{
			t = ft_expand_var(line, i, ft_spacelen(line + i));
			free(line);
			line = t;
		}
		i++;
	}
	return (line);
}
