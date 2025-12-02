/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:43:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_left_redir(t_ast_node *node, int *saved_stdin,
	int *saved_stdout)
{
	if (node->left && (node->left->type == AST_REDIR_OUT
			|| node->left->type == AST_REDIR_APPEND
			|| node->left->type == AST_REDIR_IN
			|| node->left->type == AST_REDIR_HEREDOC))
	{
		if (process_redirections_left_to_right(node->left,
				saved_stdin, saved_stdout) != 0)
			return (1);
	}
	return (0);
}

static int	check_right_redir(t_ast_node *node, int *saved_stdin,
	int *saved_stdout)
{
	if ((node->type == AST_REDIR_IN || node->type == AST_REDIR_HEREDOC)
		&& node->right && (node->right->type == AST_REDIR_OUT
			|| node->right->type == AST_REDIR_APPEND))
	{
		if (process_redirections_left_to_right(node->right,
				saved_stdin, saved_stdout) != 0)
			return (1);
	}
	return (0);
}

int	process_redirections_left_to_right(t_ast_node *node, int *saved_stdin,
	int *saved_stdout)
{
	if (!node || node->type == AST_COMMAND)
		return (0);
	if (check_left_redir(node, saved_stdin, saved_stdout) != 0)
		return (1);
	if (check_right_redir(node, saved_stdin, saved_stdout) != 0)
		return (1);
	if (node->type == AST_REDIR_OUT)
		return (process_out_redir(node, saved_stdout));
	else if (node->type == AST_REDIR_APPEND)
		return (process_append_redir(node, saved_stdout));
	else if (node->type == AST_REDIR_IN)
		return (process_in_redir(node, saved_stdin));
	else if (node->type == AST_REDIR_HEREDOC)
		return (process_heredoc_redir(node, saved_stdin));
	return (0);
}

static int	open_inter_file(t_ast_node *node)
{
	int	fd;

	if (node->type == AST_REDIR_OUT)
		fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(node->filename), 1);
	close(fd);
	return (0);
}

int	open_intermediate_files(t_ast_node *node)
{
	if (!node || (node->type != AST_REDIR_OUT
			&& node->type != AST_REDIR_APPEND))
		return (0);
	if (node->left && (node->left->type == AST_REDIR_OUT
			|| node->left->type == AST_REDIR_APPEND))
	{
		if (open_intermediate_files(node->left) != 0)
			return (1);
		if (open_inter_file(node->left) != 0)
			return (1);
	}
	return (0);
}
