#include "minishell.h"

char	*ft_test_quoted_tokens(char *line)
{
	int	i;
	int	len;
	char	*q_line;

	i = 0;
	q_line = NULL;
	len = 0;
	while (i < ft_strlen(line))
	{
		len = ft_quoted_len(line + i, '\"');
		printf("double q_len = %d\n", len);
		if (len == -1)
			break ;
		i += len;
		if (i >= ft_strlen(line))
			break ;
	}
	i = 0;
	while (i < ft_strlen(line))
	{
		len = ft_quoted_len(line + i, '\'');
		printf("simple q_len = %d\n", len);
		if (len == -1)
			break ;
		i += len;
		if (i >= ft_strlen(line))
			break ;
	}
	q_line = ft_escape_quotes(line);
	if (q_line)
		printf("q_token = 8%s8\n", q_line);
	return (q_line);
}

char	*ft_test_expansion(char *line)
{
	char	*s;
	
	if (!line)
		return (NULL);
	s = ft_expand_line(line);
	printf("expanded_line = %s\n", s);
	return (s);
}

char	**ft_test_space(char *line)
{
	int	i;
	int	len;
	char	**t;

	if (!line)
		return (NULL);
	i = 0;
	while (i < ft_strlen(line))
	{
		len = ft_sep_len(line + i);
		printf("space_len = %d\n", len);
		i += len;
	}
	len = ft_num_s_tokens(line);
	printf("num s_tokens = %d\n", len);
	i = 0;
	t = ft_token_sep(line);
	while (t[i])
		printf("spaced_token[%d] = 8%s8\n", i, t[i++]);
	return (t);
}

int	main(int argc, char **argv, char **envp)
{

	int	i = 1;
	char	*s = NULL;
	char	*q_line;
	char	**s_tokens;
	char	*e_line;
	char	*t;
	char	*x;

	printf("argv = 8%s8\n", argv[1]);
	q_line = NULL;
	e_line = NULL;
	t = NULL;
	s = ft_strdup(argv[1]);
	t = ft_trim_spaces(s);
	printf("trimmed = %s\n", t);
	free(s);
	s = ft_strdup(t);
	// x = ft_test_expansion(s);
	// free(x);
	s_tokens = ft_tokens(t);
	if (!s_tokens)
		return (free(t), 1);
	free(t);
	free(s);
	i = 0;
	while (s_tokens[i])
		printf("s_tokens[%d] = %s\n", i, s_tokens[i++]);
	ft_free_d(s_tokens);
	// free(t);
	// t = ft_strtrim(s, " ");
	// free(s);
	// if (!t)
	// 	return (1);
	// printf("argv = 8%s8\n", t);
	// q_line = ft_test_quoted_tokens(t);
	// i = 0;
	// printf("%p\n", q_line);
	// printf("q_line = 8%s8\n", q_line);
	// e_line = ft_expand_line(q_line);
	// printf("e_line = 8%s8\n", e_line);
	// s_tokens = ft_test_space(e_line);
	// ft_free_d(s_tokens);
	// free(e_line);
}
