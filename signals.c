#include "minishell.h"

void    ft_sig_parent(int signal)
{
        g_sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
}

void    ft_sig_hd(int signal)
{
        g_sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
}

void    ft_set_sig(int option)
{
        struct sigaction        sa;

        ft_memset(&sa, 0, sizeof(sa));
        if (option == PARENT)
        {
            sa.sa_handler = ft_sig_parent;
            sa.sa_flags = 0;
            sigaction(SIGINT, &sa, NULL);
            sigaction(SIGQUIT, &sa, NULL);
            return ;
        }
        if (option == HERE_DOC)
        {
            sa.sa_handler = ft_sig_hd;
            sa.sa_flags = 0;
            sigaction(SIGINT, &sa, NULL);
            sa.sa_handler = SIG_IGN;
            sigaction(SIGQUIT, &sa, NULL);
            return ;
        }
        if (option == CHILD)
        {
        	sa.sa_handler = SIG_DFL;
        	sa.sa_flags = 0;
        	sigaction(SIGINT, &sa, NULL);
        	sigaction(SIGQUIT, &sa, NULL);
		}
		return ;
}