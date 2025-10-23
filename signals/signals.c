/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:21 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/02 19:05:58 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int	get_signal(void)        :return the current value of the g_signal.
int	get_signal(void)
{
	return (g_signal);
}

// void	reset_signal(void)      :set it to 0.
void	reset_signal(void)
{
	g_signal = 0;
}
