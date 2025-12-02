/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:32:06 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_execve_error_path(char *cmd, char *cmd_path)
{
	free(cmd_path);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Permission denied\n", 20);
			exit(126);
		}
		else
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Is a directory\n", 17);
			exit(126);
		}
	}
	else
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		exit(127);
	}
}

static void	handle_execve_error(char *cmd, char *cmd_path)
{
	if (strchr(cmd, '/'))
		handle_execve_error_path(cmd, cmd_path);
	else
	{
		free(cmd_path);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

static void	execute_child_process(t_ast_node *node, char ***envp)
{
	char	*cmd_path;

	setup_child_signals();
	cmd_path = resolve_command_path(node->args[0], *envp);
	if (!cmd_path)
	{
		write(2, node->args[0], ft_strlen(node->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (execve(cmd_path, node->args, *envp) == -1)
		handle_execve_error(node->args[0], cmd_path);
}

static int	handle_parent_wait(pid_t pid)
{
	int	status;

	setup_parent_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(1, "\n", 1), 130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (write(2, "Quit (core dumped)\n", 19), 131);
	return (WIFEXITED(status) * WEXITSTATUS(status) + !WIFEXITED(status));
}

int	execute_command(t_ast_node *node, char ***envp)
{
	pid_t	pid;

	if (!node || !node->args || !node->args[0])
		return (1);
	strip_markers_from_args(node->args);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args, envp));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_child_process(node, envp);
	return (handle_parent_wait(pid));
}
