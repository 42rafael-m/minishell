#include "minishell.h"

char	**ft_test_quoted_tokens(char *line)
{
	int	i;
	int	len;
	char	**q_tokens;

	i = 0;
	while (i < ft_strlen(line))
	{
		len = ft_quoted_len(line + i);
		printf("q_len = %d\n", len);
		if (len == -1)
			return (q_tokens);
		i += len;
		if (!i >= ft_strlen(line))
			break ;
	}
	len = ft_num_q_tokens(line);
	printf("q_num = %d\n", len);
	q_tokens = ft_token_quotes(line);
	i = 0;
	while (i < len)
	{
		printf("q_token[i] = 8%s8\n", q_tokens[i]);
		i++;
	}
	return (q_tokens);
}

char	**ft_test_space(char **tokens)
{
	int	i;
	int	j;
	int	len;
	char	**t;

	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	tokens = ft_trim_tokens(tokens);
	while (i < ft_doubleptr_len((void **)tokens))
	{
		printf("line = 8%s8\n", tokens[i]);
		j = 0;
		while (j < ft_strlen(tokens[i]))
		{
			len = ft_spacelen(tokens[i] + j);
			printf("space_len = %d\n", len);
			j += len;
		}
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		len = ft_num_s_tokens(tokens[i++]);
		printf("num s_tokens = %d\n", len);
	}
	i = 0;
	while (tokens[i])
	{
		t = ft_token_space(tokens[i]);
		j = 0;
		while (t[j])
			printf("spaced_token = 8%s8\n", t[j++]);
		ft_free_d(t);
		i++;
	}
	t = ft_insert_s_tokens(tokens, 0);
	if (!t)
		return (write(2, "No inserted_tokens\n", 20), NULL);
	i = 0;
	printf("s_tokens len = %d\n", ft_doubleptr_len((void **)t));
	while (t[i])
		printf("inserted_tokens = 8%s8\n", t[i++]);
	return (t);
}

int	main(int argc, char **argv, char **envp)
{

	int	i = 1;
	char	*s = NULL;
	char	**q_tokens;
	char	**s_tokens;
	char	**x;
	char	*t;

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
	printf("argv = 8%s8\n", t);
	q_tokens = ft_test_quoted_tokens(t);
	free(t);
	i = 0;
	printf("q_tokens len = %d\n", ft_doubleptr_len((void **)q_tokens));
	while (q_tokens[i])
		printf("q_tokens[i] final = 8%s8\n", q_tokens[i++]);
	s_tokens = ft_test_space(q_tokens);
	printf("%p", s_tokens);
	ft_free_d(s_tokens);
}
