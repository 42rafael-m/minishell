/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:26 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 15:44:23 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <sys/wait.h>

# define IGNORE 1
# define DEFAULT 0
# define READ 2
# define APPEND 1
# define WRITE 0
# define SEP_STR " \n\t<>|"
# define SEP_STR2 " \n\t<>|\"\'"
# define IFS " \t\n"
# define REDIR_S "<>"
# define QUOTES "\"\'"
# define NO_VAL_VAR " !\"#$%&'()*+,-./:;<=>?@[]^`{|}~ "
# define ERR_OPEN_Q "minishell: syntax error: quotes not closed\n"
# define ESC_CHARS1 "\\\"\?$"
# define UNEX_T1 "minishell: syntax error near unexpected token '<'\n"
# define UNEX_T2 "minishell: syntax error near unexpected token '>'\n"
# define HERE_ERR "minishell: warning: here-document delimited by end-of-file (wanted `"

extern volatile sig_atomic_t	g_sigint_received;

typedef struct s_cli
{
	char			*cmd;
	char			*cmd_p;
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				is_builtin;
	struct s_cli	*next;
	int				r_mode;
	char			**env;
}	t_cli;

char	**ft_tokens(char *line);
char	**ft_token_sep(char *line);
char	**ft_trim_tokens(char **tokens);
char	**ft_insert_s_tokens(char **tokens);
char	**ft_load_env(char **envp);
char	*ft_prompt(char **envp);
char	*get_hostname(void);
char	*get_pwd(char *cwd);
char	*ft_expand_line(char *token);
char	*ft_expand_var(char	*token, int start, int end);
char	*ft_get_var(char *var_call, char **envp);
char	*ft_escaped_line(char *line, int start, int end);
char	*ft_escape_quotes(char *line);
char	*ft_expand_line(char *line);
char	*ft_trim_delim(char *token, int *option);
char	*ft_expand_heredoc(int option, t_cli *cli);
int		ft_num_quoted(char *line);
int		ft_quoted_len(char *line, char quote);
int		ft_sep_len(char *line);
int		ft_exec_shell(struct sigaction *sa, char **envp);
int		ft_num_s_tokens(char *line);
int		ft_var_len(char	*var);
int 	ft_trim_s_len(char *line);
int		ft_append(char *token, t_cli *cli);
int		ft_heredoc_len(char *line);
int		ft_delim_len(char *token);
int		ft_heredoc(char *token, t_cli *cli);
int		ft_infile(char *token, t_cli *cli);
int		ft_outfile(char *token, t_cli *cli);
void	ft_set_sig(int option);
void	ft_sig_handler(int signal);
void	ft_free_list(t_cli **cli);
void	ft_here_error(char *delim);
t_cli	*ft_parse(char	*line);
t_cli	*ft_init_list();

#endif
