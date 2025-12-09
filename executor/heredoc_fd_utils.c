/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:15:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/08 12:16:16 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_heredoc_fds(int pipe_fd, int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = -1;
	if (*saved_stdin == -1)
		return (perror("dup"), close(pipe_fd), 1);
	if (dup2(pipe_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd);
		close(*saved_stdin);
		return (1);
	}
	close(pipe_fd);
	return (0);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	if (saved_stdin != STDIN_FILENO)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}
