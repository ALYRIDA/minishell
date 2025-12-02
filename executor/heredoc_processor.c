/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredocs_helper(t_ast_node *node, char ***envp, int *status)
{
	*status = process_pipeline_heredocs(node->left, envp);
	if (*status == 130)
		return (130);
	*status = process_pipeline_heredocs(node->right, envp);
	if (*status == 130)
		return (130);
	return (0);
}

int	process_pipeline_heredocs(t_ast_node *node, char ***envp)
{
	int	status;

	status = 0;
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (process_heredocs_helper(node, envp, &status));
	else if (node->type == AST_REDIR_HEREDOC)
	{
		status = execute_heredoc(node, envp);
		if (status == 130)
			return (130);
	}
	else if (node->type == AST_REDIR_IN || node->type == AST_REDIR_OUT
		|| node->type == AST_REDIR_APPEND)
		return (process_heredocs_helper(node, envp, &status));
	return (status);
}
