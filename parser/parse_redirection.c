/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_redirection(char **tokens, int *i)
{
	t_ast_node	*redir;
	char		*filename;

	if (!tokens[*i] || !is_redirection(tokens[*i]))
		return (NULL);
	(*i)++;
	if (!tokens[*i])
		return (NULL);
	redir = create_ast_node(get_redir_type(tokens[*i - 1]));
	if (!redir)
		return (NULL);
	filename = tokens[*i];
	redir->heredoc_expand = (filename[0] != '\x02');
	redir->filename = strip_quote_marker(filename);
	if (!redir->filename)
		return (free_ast(redir), NULL);
	(*i)++;
	return (redir);
}

t_ast_node	*combine_redir_cmd(t_ast_node *cmd, t_ast_node *redir)
{
	if (!cmd || !redir)
		return (NULL);
	if (redir->type == AST_REDIR_IN || redir->type == AST_REDIR_HEREDOC)
	{
		if (cmd->type == AST_REDIR_IN || cmd->type == AST_REDIR_HEREDOC)
			return (redir->left = cmd, redir->right = cmd->right,
				cmd->right = NULL, redir);
		else
			return (redir->right = cmd, redir);
	}
	else
	{
		redir->left = cmd;
		return (redir);
	}
}

static t_ast_node	*parse_mixed_cmd_redir(char **tokens, int *i, int start_i)
{
	t_ast_node	*cmd;
	t_ast_node	*redir;
	t_ast_node	*result;

	cmd = parse_command_redirections(tokens, i);
	if (!cmd)
		return (NULL);
	*i = start_i;
	result = cmd;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0)
	{
		if (is_redirection(tokens[*i]))
		{
			redir = parse_redirection(tokens, i);
			if (!redir)
				return (free_ast(result), NULL);
			result = combine_redir_cmd(result, redir);
			if (!result)
				return (NULL);
		}
		else
			(*i)++;
	}
	return (result);
}

static t_ast_node	*parse_redir_then_cmd(char **tokens, int *i,
		t_ast_node *result)
{
	t_ast_node	*cmd;
	t_ast_node	*redir;

	if (tokens[*i] && !is_redirection(tokens[*i])
		&& ft_strcmp(tokens[*i], "|") != 0)
	{
		cmd = parse_simple_command(tokens, i);
		if (cmd)
			result = combine_redir_cmd(cmd, result);
		while (tokens[*i] && is_redirection(tokens[*i]))
		{
			redir = parse_redirection(tokens, i);
			if (!redir)
				return (free_ast(result), NULL);
			result = combine_redir_cmd(result, redir);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

t_ast_node	*parse_cmd_with_redirections(char **tokens, int *i)
{
	t_ast_node	*cmd;
	t_ast_node	*redir;
	t_ast_node	*result;
	int			start_i;

	start_i = *i;
	result = parse_mixed_cmd_redir(tokens, i, start_i);
	if (result)
		return (result);
	cmd = parse_simple_command(tokens, i);
	result = cmd;
	if (!cmd && tokens[*i] && is_redirection(tokens[*i]))
		result = create_default_cmd(tokens, *i);
	while (tokens[*i] && is_redirection(tokens[*i]))
	{
		redir = parse_redirection(tokens, i);
		if (!redir)
			return (free_ast(result), NULL);
		result = combine_redir_cmd(result, redir);
		if (!result)
			return (NULL);
	}
	if (!cmd)
		result = parse_redir_then_cmd(tokens, i, result);
	return (result);
}
