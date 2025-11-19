/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/18 17:08:44 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_ast_node *node, char ***envp)
{
	pid_t	pid;
	int		status;

	if (!node || !node->args || !node->args[0])
		return (1);
	// Strip quote markers from all arguments before execution
	strip_markers_from_args(node->args);
	if (is_builtin(node->args[0]))
		return (execute_builtin(node->args, envp));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		setup_child_signals();
		if (execvp(node->args[0], node->args) == -1)
			(write(2, node->args[0], ft_strlen(node->args[0])),
				write(2, ": command not found\n", 20), exit(127));
	}
	(setup_parent_signals(), waitpid(pid, &status, 0), setup_signals());
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (write(1, "\n", 1), 130);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (write(2, "Quit (core dumped)\n", 19), 131);
	return (WIFEXITED(status) * WEXITSTATUS(status) + !WIFEXITED(status));
}

static void	exec_pipe_child(t_ast_node *node, int *pfd, char ***envp, int n)
{
	int	exit_status;

	setup_child_signals();
	if (n == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		exit_status = execute_ast(node->left, envp);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		exit_status = execute_ast(node->right, envp);
	}
	exit(exit_status);
}

static int	wait_pipeline(pid_t *pid)
{
	int	status;

	setup_parent_signals();
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	setup_signals();
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (write(1, "\n", 1), 130);
		if (WTERMSIG(status) == SIGQUIT)
			return (write(2, "Quit (core dumped)\n", 19), 131);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_pipeline(t_ast_node *node, char ***envp)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid[0] == 0)
		exec_pipe_child(node, pipe_fd, envp, 0);
	pid[1] = fork();
	if (pid[1] == -1)
		return (perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid[1] == 0)
		exec_pipe_child(node, pipe_fd, envp, 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_pipeline(pid));
}

int	execute_ast(t_ast_node *node, char ***envp)
{
	if (!node)
		return (0);
	if (node->type == AST_COMMAND)
		return (execute_command(node, envp));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, envp));
	else if (node->type == AST_REDIR_IN)
		return (execute_redirect_in(node, envp));
	else if (node->type == AST_REDIR_OUT)
		return (execute_redirect_out(node, envp));
	else if (node->type == AST_REDIR_APPEND)
		return (execute_redirect_append(node, envp));
	else if (node->type == AST_REDIR_HEREDOC)
		return (execute_heredoc(node, envp));
	return (1);
}
