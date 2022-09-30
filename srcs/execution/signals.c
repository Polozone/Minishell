
#include "../../includes/minishell.h"

extern int	g_error;

void		sig_handler_hd()
{

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	_sig_stp_main(int sig)
{
	if (sig == 2)
	{
		printf("OKTEST\n");
		// printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error = 130;
	}
}

void	sig_parent(void)
{
	signal(SIGQUIT, sig_quit_exec);
	signal(SIGINT, sig_int_exec);
}

void	sig_quit_exec(int signo)
{
	printf("tost\n");
	g_error = 131;
	write(1, "Quit: 3\n", 8);
}

void	sig_int_exec(int signo)
{
	printf("test\n");
	write(2, "\n", 1);
}