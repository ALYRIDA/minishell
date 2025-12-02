/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:32:06 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_overflow(char *str)
{
	int		i;
	int		len;
	char	*max_long;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	len = ft_strlen(str + i);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (str[0] == '-')
		max_long = "9223372036854775808";
	else
		max_long = "9223372036854775807";
	while (str[i])
	{
		if (str[i] > max_long[i - (str[0] == '-' || str[0] == '+')])
			return (1);
		if (str[i] < max_long[i - (str[0] == '-' || str[0] == '+')])
			return (0);
		i++;
	}
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]) || is_overflow(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	exit(exit_code);
	return (0);
}
