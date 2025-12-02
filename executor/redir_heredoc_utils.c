/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:56:33 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_redir(t_ast_node *node, int *saved_stdin)
{
	if (node->heredoc_fd == -1)
		return (1);
	if (*saved_stdin == -1)
		*saved_stdin = dup(STDIN_FILENO);
	if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
		return (perror("dup2"), 1);
	return (0);
}
