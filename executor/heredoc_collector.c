/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc_new.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:56:33 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_child_process(int *pipe_fd, t_ast_node *node,
		char ***envp)
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

static int	finish_heredoc_collection(pid_t pid, int *pipe_fd,
		t_ast_node *node)
{
	int	exit_status;

	close(pipe_fd[1]);
	setup_heredoc_parent_signals();
	exit_status = wait_for_heredoc_child(pid);
	setup_signals();
	if (exit_status == 130)
		return (close(pipe_fd[0]), 130);
	node->heredoc_fd = pipe_fd[0];
	return (0);
}

static int	collect_single_heredoc(t_ast_node *node, char ***envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (!node || !node->filename || node->heredoc_fd != -1)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
		handle_heredoc_child_process(pipe_fd, node, envp);
	return (finish_heredoc_collection(pid, pipe_fd, node));
}

static int	collect_heredocs_helper(t_ast_node *node, char ***envp, int *status)
{
	*status = collect_pipeline_heredocs(node->left, envp);
	if (*status == 130)
		return (130);
	*status = collect_pipeline_heredocs(node->right, envp);
	if (*status == 130)
		return (130);
	return (0);
}

int	collect_pipeline_heredocs(t_ast_node *node, char ***envp)
{
	int	status;

	status = 0;
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (collect_heredocs_helper(node, envp, &status));
	else if (node->type == AST_REDIR_HEREDOC)
	{
		status = collect_single_heredoc(node, envp);
		if (status == 130)
			return (130);
	}
	else if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_REDIR_APPEND)
		return (collect_heredocs_helper(node, envp, &status));
	return (status);
}
