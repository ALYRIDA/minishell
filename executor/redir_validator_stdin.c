/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_validate2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_stdin_node(t_ast_node *node)
{
	int	fd;

	if (node->type != AST_REDIR_IN)
		return (0);
	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		return (perror(node->filename), 1);
	close(fd);
	return (0);
}

int	validate_redirections_stdin(t_ast_node *node)
{
	int	current_result;
	int	left_result;
	int	right_result;

	current_result = 0;
	left_result = 0;
	right_result = 0;
	if (!node)
		return (0);
	current_result = validate_stdin_node(node);
	if (node->left && (node->left->type == AST_REDIR_IN
			|| node->left->type == AST_REDIR_HEREDOC))
		left_result = validate_redirections_stdin(node->left);
	if (node->right && (node->right->type == AST_REDIR_IN
			|| node->right->type == AST_REDIR_HEREDOC))
		right_result = validate_redirections_stdin(node->right);
	return (current_result || left_result || right_result);
}
