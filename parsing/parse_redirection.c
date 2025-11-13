/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/12 11:05:14 by aareslan         ###   ########.fr       */
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
	if (filename[0] == '\x02')
		redir->filename = ft_strdup(filename + 1);
	else
		redir->filename = ft_strdup(filename);
	if (!redir->filename)
		return (free_ast(redir), NULL);
	(*i)++;
	return (redir);
}

static t_ast_node	*combine_redir_cmd(t_ast_node *cmd, t_ast_node *redir)
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

static t_ast_node	*create_default_cmd(void)
{
	t_ast_node	*result;

	result = create_ast_node(AST_COMMAND);
	if (!result)
		return (NULL);
	result->args = malloc(sizeof(char *) * 2);
	if (!result->args)
		return (free_ast(result), NULL);
	result->args[0] = ft_strdup("cat");
	result->args[1] = NULL;
	return (result);
}

t_ast_node	*parse_cmd_with_redirections(char **tokens, int *i)
{
	t_ast_node	*cmd;
	t_ast_node	*redir;
	t_ast_node	*result;

	cmd = parse_simple_command(tokens, i);
	result = cmd;
	if (!cmd && tokens[*i] && is_redirection(tokens[*i]))
		result = create_default_cmd();
	while (tokens[*i] && is_redirection(tokens[*i]))
	{
		redir = parse_redirection(tokens, i);
		if (!redir)
			return (free_ast(result), NULL);
		result = combine_redir_cmd(result, redir);
		if (!result)
			return (NULL);
	}
	return (result);
}
