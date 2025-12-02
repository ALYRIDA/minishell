/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:11:29 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipe_rec_base(t_ast_node *node, char ***envp, int input_fd,
		int *last_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (input_fd != 0)
		{
			if (dup2(input_fd, 0) == -1)
				return (perror("dup2"), close(input_fd), exit(1), 1);
			close(input_fd);
		}
		exit(execute_ast(node, envp));
	}
	if (input_fd != 0)
		close(input_fd);
	*last_pid = pid;
	return (0);
}

static int	exec_pipe_rec_right(t_ast_node *node, char ***envp, int pipe_fd,
		int *last_pid)
{
	pid_t	right_pid;

	if (node->right && node->right->type == AST_PIPE)
		return (exec_pipeline_recursive(node->right, envp, pipe_fd, last_pid));
	else if (node->right)
	{
		right_pid = fork();
		if (right_pid == 0)
		{
			setup_child_signals();
			if (dup2(pipe_fd, 0) == -1)
				return (perror("dup2"), close(pipe_fd), exit(1), 1);
			close(pipe_fd);
			exit(execute_ast(node->right, envp));
		}
		close(pipe_fd);
		*last_pid = right_pid;
		return (0);
	}
	close(pipe_fd);
	return (0);
}

static int	exec_pipe_left(int input_fd, int *pipe_fd, t_ast_node *node,
		char ***envp)
{
	setup_child_signals();
	if (dup2(input_fd, 0) == -1 && input_fd != 0)
	{
		perror("dup2");
		if (input_fd != 0)
			close(input_fd);
		return (close(pipe_fd[0]), close(pipe_fd[1]), exit(1), 1);
	}
	if (input_fd != 0)
		close(input_fd);
	if (dup2(pipe_fd[1], 1) == -1)
		return (perror("dup2"), close(pipe_fd[0]), close(pipe_fd[1]),
			exit(1), 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(execute_ast(node->left, envp));
}

int	exec_pipeline_recursive(t_ast_node *node, char ***envp,
		int input_fd, int *last_pid)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!node || node->type != AST_PIPE)
		return (exec_pipe_rec_base(node, envp, input_fd, last_pid));
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
		exec_pipe_left(input_fd, pipe_fd, node, envp);
	close(pipe_fd[1]);
	if (input_fd != 0)
		close(input_fd);
	return (exec_pipe_rec_right(node, envp, pipe_fd[0], last_pid));
}
