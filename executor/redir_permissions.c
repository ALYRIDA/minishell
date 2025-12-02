/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_permission.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir_permissions(char *dir_path, const char *filename)
{
	int	dir_result;

	dir_result = access(dir_path, W_OK | X_OK);
	if (dir_result != 0)
	{
		write_permission_error(filename);
		free(dir_path);
		return (1);
	}
	free(dir_path);
	return (0);
}

static int	check_new_file_dir(const char *filename)
{
	char	*last_slash;
	char	*dir_path;
	int		slash_pos;

	last_slash = find_last_slash(filename);
	if (last_slash)
	{
		slash_pos = last_slash - filename;
		if (slash_pos == 0)
			dir_path = ft_strdup("/");
		else
			dir_path = ft_substr_dup(filename, 0, slash_pos);
		if (!dir_path)
			return (1);
		return (check_dir_permissions(dir_path, filename));
	}
	else
	{
		if (access(".", W_OK | X_OK) != 0)
		{
			write_permission_error(filename);
			return (1);
		}
	}
	return (0);
}

static int	check_output_perms(t_ast_node *node)
{
	if (access(node->filename, F_OK) == 0)
	{
		if (access(node->filename, W_OK) != 0)
		{
			write_permission_error(node->filename);
			return (1);
		}
	}
	else
		return (check_new_file_dir(node->filename));
	return (0);
}

static int	check_validate_left(t_ast_node *node)
{
	int	result;

	if (node->left && (node->left->type == AST_REDIR_OUT
			|| node->left->type == AST_REDIR_APPEND
			|| node->left->type == AST_REDIR_IN
			|| node->left->type == AST_REDIR_HEREDOC))
	{
		result = validate_all_redirections_before_open(node->left);
		if (result != 0)
			return (result);
	}
	return (0);
}

int	validate_all_redirections_before_open(t_ast_node *node)
{
	int	result;

	if (!node || node->type == AST_COMMAND)
		return (0);
	result = check_validate_left(node);
	if (result != 0)
		return (result);
	if (node->type == AST_REDIR_OUT || node->type == AST_REDIR_APPEND)
		return (check_output_perms(node));
	else if (node->type == AST_REDIR_IN)
	{
		if (access(node->filename, F_OK) != 0)
			return (perror(node->filename), 1);
		if (access(node->filename, R_OK) != 0)
		{
			write_permission_error(node->filename);
			return (1);
		}
	}
	return (0);
}
