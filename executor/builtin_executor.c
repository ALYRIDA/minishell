/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:18:59 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(char **args, char ***envp)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, envp));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, envp));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	else if (ft_strcmp(args[0], ":") == 0)
		return (0);
	return (1);
}
