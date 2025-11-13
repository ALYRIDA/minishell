/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:52:42 by skhalil           #+#    #+#             */
/*   Updated: 2025/10/22 10:43:10 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_flag(char *arg)
{
	int	k;

	if (!arg || arg[0] != '-')
		return (0);
	k = 1;
	if (!arg[k])
		return (0);
	while (arg[k])
	{
		if (arg[k] != 'n')
			return (0);
		k++;
	}
	return (1);
}

int	skip_n_flags(char **argv, int *newline)
{
	int	i;

	i = 1;
	*newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		*newline = 0;
		i++;
	}
	return (i);
}

void	print_args(char **argv, int i, int newline)
{
	int	j;

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			write(1, &argv[i][j++], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

int	ft_echo(char **argv)
{
	int	newline;
	int	start;

	if (!argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	start = skip_n_flags(argv, &newline);
	print_args(argv, start, newline);
	return (0);
}
