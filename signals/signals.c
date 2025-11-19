/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:21 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/18 18:39:12 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Signal handler for heredoc (in child process)
static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

// rl_on_new_line  : tells Readline that the cursor is on a new line.
// rl_replace_line : clears the current input line.
// rl_redisplay    : redraws the prompt.
static void	handle_sigint(int sig)
{
	int	i;

	i = 0;
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	while (i < 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		i++;
	}
}

//signal(SIGINT, handle_sigint) :CTRL-C.
/*signal(SIGQUIT, SIG_IGN)      :CTRL-\.*/
//signal(SIGTSTP, SIG_IGN)      :CTRL-Z.
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// Setup signals for heredoc child process
void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// Setup signals for child processes (external commands)
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
