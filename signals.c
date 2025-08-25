#include "minishell.h"

void    ft_sig_handler(int signal)
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
                sa.sa_handler = ft_sig_handler;
                sa.sa_flags = 0;
                sigaction(SIGINT, &sa, NULL);
                sigaction(SIGQUIT, &sa, NULL);
                return ;
        }
	if (option = 2)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		return ;
	}
        sa.sa_handler = SIG_DFL;
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
        return ;
}