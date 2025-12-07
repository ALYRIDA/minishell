/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/07 17:41:11 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_fds_return(int saved_stdout, int saved_stdin, int status)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	return (status);
}

int	exec_redir_common(t_ast_node *node, char ***envp)
{
	int			saved_stdout;
	int			saved_stdin;
	int			exit_status;
	t_ast_node	*actual_cmd;

	saved_stdout = -1;
	saved_stdin = -1;
	if (process_all_heredocs_first(node, envp) == 130)
		return (130);
	if (process_redirections_left_to_right(node, &saved_stdin,
			&saved_stdout) != 0)
		return (restore_fds_return(saved_stdout, saved_stdin, 1));
	actual_cmd = find_command_node(node);
	exit_status = execute_ast(actual_cmd, envp);
	return (restore_fds_return(saved_stdout, saved_stdin, exit_status));
}

int	execute_redirect_stdin(t_ast_node *node, char ***envp)
{
	return (exec_redir_common(node, envp));
}

int	execute_redirect_out(t_ast_node *node, char ***envp)
{
	return (exec_redir_common(node, envp));
}

int	execute_redirect_append(t_ast_node *node, char ***envp)
{
	return (exec_redir_common(node, envp));
}
