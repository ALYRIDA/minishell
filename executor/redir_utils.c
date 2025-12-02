/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:56:33 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_last_slash(const char *str)
{
	char	*last;
	char	*current;

	if (!str)
		return (NULL);
	last = NULL;
	current = (char *)str;
	while (*current)
	{
		if (*current == '/')
			last = current;
		current++;
	}
	return (last);
}

t_ast_node	*find_command_node(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == AST_COMMAND)
		return (node);
	if (node->type == AST_REDIR_IN || node->type == AST_REDIR_HEREDOC)
		return (find_command_node(node->right));
	else if (node->type == AST_REDIR_OUT || node->type == AST_REDIR_APPEND)
		return (find_command_node(node->left));
	return (NULL);
}

int	process_out_redir(t_ast_node *node, int *saved_stdout)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(node->filename), 1);
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	process_append_redir(t_ast_node *node, int *saved_stdout)
{
	int	fd;

	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(node->filename), 1);
	if (*saved_stdout == -1)
		*saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	process_in_redir(t_ast_node *node, int *saved_stdin)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
		return (perror(node->filename), 1);
	if (*saved_stdin == -1)
		*saved_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
