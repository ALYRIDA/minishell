/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:18:59 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:43:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_heredoc_child(int *pipe_fd, t_ast_node *node, char ***envp)
{
	close(pipe_fd[0]);
	setup_heredoc_signals();
	if (node->left)
		consume_all_chained_heredocs(node->left);
	read_heredoc_content(pipe_fd[1], node->filename,
		node->heredoc_expand, *envp);
	close(pipe_fd[1]);
	exit(0);
}

static int	handle_heredoc_parent(int *pipe_fd, pid_t pid)
{
	int	exit_status;

	close(pipe_fd[1]);
	setup_heredoc_parent_signals();
	exit_status = wait_for_heredoc_child(pid);
	setup_signals();
	if (exit_status == 130)
	{
		close(pipe_fd[0]);
		return (130);
	}
	return (exit_status);
}

static int	execute_with_heredoc(int pipe_fd, t_ast_node *node, char ***envp)
{
	int	saved_stdin;
	int	exit_status;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (perror("dup"), close(pipe_fd), 1);
	if (dup2(pipe_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd);
		close(saved_stdin);
		return (1);
	}
	close(pipe_fd);
	exit_status = execute_ast(node->right, envp);
	if (saved_stdin != STDIN_FILENO)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	return (exit_status);
}

int	execute_heredoc(t_ast_node *node, char ***envp)
{
	int		pipe_fd[2];
	int		exit_status;
	pid_t	pid;

	if (!node || !node->filename)
		return (1);
	if (node->heredoc_fd != -1)
		return (execute_with_heredoc(node->heredoc_fd, node, envp));
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
		handle_heredoc_child(pipe_fd, node, envp);
	exit_status = handle_heredoc_parent(pipe_fd, pid);
	if (exit_status == 130)
		return (130);
	return (execute_with_heredoc(pipe_fd[0], node, envp));
}
