/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_validate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_left_redir(t_ast_node *node)
{
	int	result;

	if (node->left && (node->left->type == AST_REDIR_OUT
			|| node->left->type == AST_REDIR_APPEND
			|| node->left->type == AST_REDIR_IN
			|| node->left->type == AST_REDIR_HEREDOC))
	{
		result = validate_all_redirections(node->left);
		if (result != 0)
			return (result);
	}
	return (0);
}

static int	validate_out_redir(t_ast_node *node)
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

static int	validate_in_redir(t_ast_node *node)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		return (perror(node->filename), 1);
	close(fd);
	return (0);
}

int	validate_all_redirections(t_ast_node *node)
{
	int	result;

	if (!node || node->type == AST_COMMAND)
		return (0);
	result = validate_left_redir(node);
	if (result != 0)
		return (result);
	if (node->type == AST_REDIR_OUT || node->type == AST_REDIR_APPEND)
		return (validate_out_redir(node));
	else if (node->type == AST_REDIR_IN)
		return (validate_in_redir(node));
	return (0);
}
