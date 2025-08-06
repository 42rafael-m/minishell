#include "minishell.h"

int ft_trim_s_len(char *line)
{
	int		i;
	int		len;
	char	sep;

	i = 0;
	len = 0;
	while (line && ft_isspace(line[i]))
		i++;
	while (line && i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			sep = line[i];
			len += ft_quoted_len(line + i, sep);
			i += ft_quoted_len(line + i, sep);
		}
		while (ft_isspace(line[i]) && ft_isspace(line[i + 1]))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*ft_trim_spaces(char *line)
{
	int		i;
	int		j;
	char	sep;
	char	*trimmed;

	i = 0;
	j = 0;
	sep = '\0';
	trimmed = ft_calloc(ft_trim_s_len(line), sizeof(char));
	while (line && ft_isspace(line[i]))
		i++;
	while (trimmed && line && line[i])
	{
		while (sep == '\0' && ft_isspace(line[i]) && (ft_isspace(line[i + 1]) || !line[i + 1]))
			i++;
		if (sep && line[i] == sep)
		{
			sep = '\0';
			trimmed[j++] = line[i++];
			continue ;
		}
		if (ft_strchr(QUOTES, line[i]))
			sep = line[i];
		trimmed[j++] = line[i++];
	}
	return (trimmed);
}

void	ft_sig_handler(int signal)
{
	struct sigaction sa;

    sigint_received = 1;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay(); 
}

void	ft_set_sig(int option)
{
	struct sigaction sa;

 	if (option == 1)
    {
        sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
        return;
    }
    sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
	return ;
}