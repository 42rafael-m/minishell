#include "minishell.h"

#include "minishell.h"

char	*get_pwd(char *cwd)
{
	char	*home;
	char	*pwd;
	char	*t;

	if (!cwd)
		return (NULL);
	home = ft_strtrim(getenv("HOME"), "HOME=");
	if (!home)
		return (NULL);
	if (!ft_strncmp(home, cwd, ft_strlen(home)))
	{
		t = ft_strtrim(cwd, home);
		pwd = ft_strjoin("~/", t);
		return (free(home), free(t), pwd);
	}
	pwd = ft_strdup(cwd);
	return(free(home), pwd);
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
		return (free(buffer), NULL);
	read(fd, buffer, 1);
	while (buffer[0] != '\n' && buffer[0] != EOF)
	{
		t = r;
		r = ft_strjoin(r, buffer);
		read(fd, buffer, 1);
		free(t);
	}
	return (free(buffer), close(fd), r);
}

char	*ft_prompt(char **envp)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	char	*t;

	user = ft_strtrim(getenv("USER"), "USER=");
	t = (char *)ft_calloc(4096, sizeof(char));
	if (!t || ! user)
		return (NULL);
	pwd = get_pwd(getcwd(t, 4096));
	free(t);
	prompt = ft_strjoin(user, "@");
	free(user);
	user = get_hostname();
	t = ft_strjoin(prompt, user);
	free(user);
	free(prompt);
	prompt = ft_strjoin(t, ":");
	free(t);
	t = ft_strjoin(prompt, pwd);
	free(prompt);
	prompt = ft_strjoin(t, "$ ");
	return (free(t), free(pwd), prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cl;
	char	**args;
	char	*prompt;
	int	i;

	i = 0;
	cl = ft_strdup("a");
	if (!cl)
		return (1);
	while (ft_strncmp(cl, "exit", 4))
	{
		i = 0;
		free(cl);
		prompt = ft_prompt(envp);
		cl = readline(prompt);
		args = ft_argv(cl);
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			write(1, "\n", 1);
			i++;
		}
		free(prompt);
		add_history(cl);
	}
	free(cl);
	rl_clear_history();
	return (0);
}