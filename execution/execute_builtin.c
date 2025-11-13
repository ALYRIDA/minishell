/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:18:59 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/06 15:26:01 by aareslan         ###   ########.fr       */
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
	return (1);
}
