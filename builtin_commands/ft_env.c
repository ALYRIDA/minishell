/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:09:43 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/05 19:54:43 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **argv, char **envp)
{
	int	i;

	if (!envp)
		return (1);
	if (argv[1])
	{
		write(2, "env: '", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "': No such file or directory\n", 30);
		return (127);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
