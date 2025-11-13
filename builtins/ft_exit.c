/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/07 16:30:00 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args)
{
	int	exit_code;

	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	exit_code = ft_atoi(args[1]);
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	exit(exit_code);
	return (0);
}
