/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:43:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_last_child(int last_pid, int *last_status)
{
	int		status;
	pid_t	wpid;

	setup_parent_signals();
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
			*last_status = status;
		wpid = wait(&status);
	}
	setup_signals();
	if (WIFEXITED(*last_status))
		return (WEXITSTATUS(*last_status));
	if (WIFSIGNALED(*last_status))
	{
		if (WTERMSIG(*last_status) == SIGINT)
			return (write(1, "\n", 1), 130);
		if (WTERMSIG(*last_status) == SIGQUIT)
			return (write(2, "Quit (core dumped)\n", 19), 131);
	}
	return (1);
}

int	execute_pipeline(t_ast_node *node, char ***envp)
{
	int	last_pid;
	int	last_status;
	int	heredoc_status;

	last_pid = -1;
	last_status = 0;
	if (!node)
		return (1);
	heredoc_status = collect_pipeline_heredocs(node, envp);
	if (heredoc_status == 130)
		return (130);
	exec_pipeline_recursive(node, envp, 0, &last_pid);
	return (wait_last_child(last_pid, &last_status));
}
