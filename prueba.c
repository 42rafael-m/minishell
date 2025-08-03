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
		if (!i >= ft_strlen(line))
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
		if (!i >= ft_strlen(line))
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

// char	**ft_test_space(char **tokens)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	char	**t;

// 	if (!tokens)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	tokens = ft_trim_tokens(tokens);
// 	while (i < ft_doubleptr_len((void **)tokens))
// 	{
// 		printf("line = 8%s8\n", tokens[i]);
// 		j = 0;
// 		while (j < ft_strlen(tokens[i]))
// 		{
// 			len = ft_spacelen(tokens[i] + j);
// 			printf("space_len = %d\n", len);
// 			j += len;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		len = ft_num_s_tokens(tokens[i++]);
// 		printf("num s_tokens = %d\n", len);
// 	}
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		t = ft_token_space(tokens[i]);
// 		j = 0;
// 		while (t[j])
// 			printf("spaced_token = 8%s8\n", t[j++]);
// 		ft_free_d(t);
// 		i++;
// 	}
// 	t = ft_insert_s_tokens(tokens);
// 	if (!t)
// 		return (write(2, "No inserted_tokens\n", 20), NULL);
// 	i = 0;
// 	printf("s_tokens len = %d\n", ft_doubleptr_len((void **)t));
// 	while (t[i])
// 		printf("inserted_tokens = 8%s8\n", t[i++]);
// 	return (t);
// }

int	main(int argc, char **argv, char **envp)
{

	int	i = 1;
	char	*s = NULL;
	char	*q_line;
	char	**s_tokens;
	char	*e_line;
	char	*t;

	q_line = NULL;
	e_line = NULL;
	t = NULL;
	while (argv[i])
	{

		t = ft_strjoin(s, argv[i]);
		free(s);
		s = ft_strjoin(t, " ");
		free(t);
		i++;
	}
	t = ft_strtrim(s, " ");
	free(s);
	if (!t)
		return (1);
	printf("argv = 8%s8\n", t);
	q_line = ft_test_quoted_tokens(t);
	// if (t != q_line)
	// 	free(t);
	i = 0;
	printf("%p\n", q_line);
	printf("q_line = 8%s8\n", q_line);
	e_line = ft_expand_line(q_line);
	// if (q_line != e_line)
	// 	free(q_line);
	printf("e_line = 8%s8\n", e_line);
	free(e_line);
	// s_tokens = ft_test_space(q_line);
	// printf("%p", s_tokens);
	// ft_free_d(s_tokens);
}
