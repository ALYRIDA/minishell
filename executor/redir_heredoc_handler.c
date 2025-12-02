/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_all_heredocs_first(t_ast_node *node, char ***envp)
{
	int	status;

	status = 0;
	if (!node)
		return (0);
	if (node->left)
		status = process_all_heredocs_first(node->left, envp);
	if (status == 130)
		return (130);
	if (node->type == AST_REDIR_HEREDOC)
	{
		status = execute_heredoc(node, envp);
		if (status == 130)
			return (130);
	}
	return (status);
}
