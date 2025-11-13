/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:18:10 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/11 21:18:40 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Setup signals for parent waiting on child
void	setup_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
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
