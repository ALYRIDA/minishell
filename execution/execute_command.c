/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:36:33 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/06 23:23:26 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_command(t_ast_node *node, char ***envp)
{
	pid_t	pid;
	int		status;

	if (!node || !node->args || !node->args[0])
		return (1);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args, envp));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (execvp(node->args[0], node->args) == -1)
		{
			perror(node->args[0]);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
