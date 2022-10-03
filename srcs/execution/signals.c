
#include "../../includes/minishell.h"

extern int	g_error;

void		sig_handler_hd()
{
	dprintf(2, "je passe dans sig_handler_hd\n");	
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	_sig_stp_main(int sig)
{
	dprintf(2, "\n\nsig = %d\n\n", sig);
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error = 1;
	}
	// if (sig == SIGQUIT)
	// {
	// 	dprintf(2, "NAS\n");
	// 	g_error = 131;
	// 	write(2, "Quit: 3\n", 8);
	// }
}
