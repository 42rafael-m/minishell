#include "minishell.h"

void    ft_sig_parent(int signal)
{
	char nl;

	nl = '\n';
    g_sigint_received = 1;
	if (signal == SIGINT)
		write(1, "^C", 2);
    ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

void    ft_sig_hd(int signal)
{
	char nl;

	nl = '\n';
    g_sigint_received = 1;
	if (signal == SIGINT)
		write(1, "^C", 2);
    ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

void    ft_set_sig(int option)
{
    struct sigaction        sa;

    ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask); 
    if (option == PARENT)
    {
        sa.sa_handler = ft_sig_parent;
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
        sa.sa_flags = 0;
        sigaction(SIGQUIT, &sa, NULL);
        // sigaction(SIGQUIT, &sa, NULL);
    }
    if (option == HERE_DOC)
    {
        sa.sa_handler = ft_sig_hd;
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sa.sa_handler = SIG_IGN;
        sigaction(SIGQUIT, &sa, NULL);
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