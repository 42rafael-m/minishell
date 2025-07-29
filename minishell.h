#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/resource.h>

typedef struct s_cli
{
	char	*cmd;
	char	**args;
	int	fdin;
	int	fdout;
	char	*heredoc;
	int	is_builtin;
	struct s_cli	*next;
}	t_cli;

#endif