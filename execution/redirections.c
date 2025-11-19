/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/18 18:39:34 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_stdin_and_execute(int fd, int saved_stdin,
	t_ast_node *node, char ***envp)
{
	int	exit_status;

	dup2(fd, STDIN_FILENO);
	close(fd);
	exit_status = execute_ast(node->right, envp);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (exit_status);
}

int	execute_redirect_in(t_ast_node *node, char ***envp)
{
	int	fd;
	int	saved_stdin;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(node->filename);
		return (1);
	}
	saved_stdin = dup(STDIN_FILENO);
	return (restore_stdin_and_execute(fd, saved_stdin, node, envp));
}

static int	restore_stdout_and_execute(int fd, int saved_stdout,
	t_ast_node *node, char ***envp)
{
	int	exit_status;

	dup2(fd, STDOUT_FILENO);
	close(fd);
	exit_status = execute_ast(node->left, envp);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (exit_status);
}

int	execute_redirect_out(t_ast_node *node, char ***envp)
{
	int	fd;
	int	saved_stdout;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(node->filename);
		return (1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	return (restore_stdout_and_execute(fd, saved_stdout, node, envp));
}

int	execute_redirect_append(t_ast_node *node, char ***envp)
{
	int	fd;
	int	saved_stdout;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(node->filename);
		return (1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	return (restore_stdout_and_execute(fd, saved_stdout, node, envp));
}
