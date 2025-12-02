/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_restore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_execute_stdin(int fd, int saved_stdin,
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
