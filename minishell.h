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
# define APPEND 1
# define WRITE 0
# define SEP_STR " <>\"\'"
# define REDIR_S "<>"
# define QUOTES "\"\'"
# define NO_VAL_VAR " !\"#$%&'()*+,-./:;<=>?@[]^`{|}~ "
# define ERR_OPEN_Q "minishell: syntax error: quotes not closed\n"

extern volatile sig_atomic_t sigint_received;

typedef struct s_cli
{
	char	*cmd;
	char	*cmd_p;
	char	**args;
	int	fdin;
	int	fdout;
	char	*delim;
	int	is_builtin;
	struct s_cli	*next;
	int	r_mode;
}	t_cli;

char	*ft_prompt(char **envp);
char	*get_hostname(void);
char	*get_pwd(char *cwd);
char	*ft_expand_token(char *token);
char	*ft_expand_var(char	*token, int start, int end);
char	*ft_get_var(char *var_call, char **envp);
char	**ft_token_quotes(char *line);
char	**ft_tokens(char *line);
char	**ft_token_space(char *line);
char	**ft_trim_tokens(char **tokens);
char	**ft_insert_s_tokens(char **tokens);
int		ft_num_q_tokens(char *line);
int		ft_quoted_len(char *line);
int		ft_spacelen(char *line);
int		ft_exec_shell(struct sigaction *sa, char **envp);
int		ft_num_s_tokens(char *line);
void	ft_set_sig(int option);
void	ft_sig_handler(int signal);
void	ft_init_list(t_cli *cli);
t_cli	*ft_parse(char	*line);

#endif