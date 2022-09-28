
#include "../../includes/minishell.h"

void		sig_handler_hd()
{
	write(1, "\n", 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	_sig_stp_main(int sig)
{
	if (sig == 2)
	{
		// dprintf(2, "OKTEST");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_parent(void)
{
	signal(SIGQUIT, sig_quit_exec);
	signal(SIGINT, sig_int_exec);
}

void	sig_quit_exec(int signo)
{
	write(1, "Quit: 3\n", 8);
}

void	sig_int_exec(int signo)
{
	write(2, "\n", 1);
}