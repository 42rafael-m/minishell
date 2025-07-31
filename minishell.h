#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/resource.h>
# include <dirent.h>
# include <signal.h>

# define IGNORE 1
# define DEFAULT 0
# define SEP_STR " \"\'"

extern volatile sig_atomic_t sigint_received;

typedef struct s_cli
{
	char	*cmd;
	char	*cmd_p;
	char	**args;
	int	fdin;
	int	fdout;
	char	*heredoc;
	int	is_builtin;
	struct s_cli	*next;
}	t_cli;

char	*ft_prompt(char **envp);
char	*get_hostname(void);
char	*get_pwd(char *cwd);
int	ft_tokenlen(char *cl);
int	ft_num_token(char	*cl);
char	**ft_tokens(char *cl);
void	ft_set_sig(int option);
void	ft_sig_handler(int signal);
int	ft_exec_shell(struct sigaction *sa, char **envp);

#endif