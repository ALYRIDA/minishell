/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:22:56 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_ast_node *node, char ***envp)
{
	if (!node)
		return (0);
	if (node->type == AST_COMMAND)
		return (execute_command(node, envp));
	else if (node->type == AST_PIPE)
		return (execute_pipeline(node, envp));
	else if (node->type == AST_REDIR_IN)
		return (execute_redirect_stdin(node, envp));
	else if (node->type == AST_REDIR_OUT)
		return (execute_redirect_out(node, envp));
	else if (node->type == AST_REDIR_APPEND)
		return (execute_redirect_append(node, envp));
	else if (node->type == AST_REDIR_HEREDOC)
		return (execute_heredoc(node, envp));
	return (1);
}
