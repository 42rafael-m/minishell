#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/resource.h>

char	*get_user(char **s)
{
	int	i = 0;
	char	*r;

	if (!s)
		return (NULL);
	while (s[i])
	{
		if (strstr(s[i], "USERNAME"))
		{
			r = ft_strtrim(s[i], "USERNAME= ");
			return (r);
		}
		i++;
	}
	return (NULL);
}

char	*get_pwd(char **s, char *user)
{
	int	i;
	char	*r;
	char	*t;
	char	*x;

	x = ft_strjoin("PWD=/home/", user);
	i = 0;
	while (s[i++])
	{
		if (strstr(s[i - 1], x))
		{
			r = ft_strtrim(s[i - 1], "PWD=home/");
			t = ft_strtrim(r, user);
			free(r);
			r = ft_strjoin("~", t);
			return (free(t), free(x), r);
		}
		if (strstr(s[i - 1], "PWD="))
		{
			r = ft_strtrim(s[i - 1], "PWD= ");
			return (free(x), r);
		}		
	}
	return (free(x), NULL);
}

char	*get_hostname(void)
{
	char	*r;
	char	*buffer;
	char	*t;
	int	fd;

	r = NULL;
	fd = open("/etc/hostname", O_RDONLY);
	buffer = ft_calloc(2, sizeof(char));
	if (fd == -1 || ! buffer)
		return (NULL);
	read(fd, buffer, 1);
	while (buffer[0] != '\n' && buffer[0] != EOF)
	{
		t = r;
		r = ft_strjoin(r, buffer);
		read(fd, buffer, 1);
		free(t);
	}
	return (close(fd), r);
}

int main(int argc, char **argv, char **envp)
{
	char	*s;
	char	*user;
	char	*hostname;
	char	*prompt;

	hostname = get_hostname();
	user = get_user(envp);
	prompt = ft_strjoin(user, "@");
	s = ft_strjoin(prompt, hostname);
	free(prompt);
	prompt = ft_strjoin(s, ":");
	char	*pwd = get_pwd(envp, user);
	free(s);
	s = ft_strjoin(prompt, pwd);
	char	*shell = ft_strjoin(s, "$ ");
	free(user);
	free(pwd);
	while (ft_strncmp(s, "exit", 5))
	{
		free(s);
		s = readline(shell);
		if (!s)
			break ;
		add_history(s);
		printf("%s\n", s);
		// printf("%s\n", s);
		// rl_on_new_line();
	}
	free(shell);
	free(hostname);
	rl_clear_history();
	// getrusage();
	return (0);
}