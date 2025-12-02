/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:21 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/19 13:56:46 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int status)
{
	if (status == 0)
		g_signal = 0;
	else
		g_signal = -status;
}

int	get_exit_status(void)
{
	if (g_signal <= 0)
		return (-g_signal);
	return (0);
}
