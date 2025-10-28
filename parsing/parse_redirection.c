/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/27 19:43:43 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_redirection(char **tokens, int *i)
{
	t_ast_node	*redir;
	char		*redir_token;

	if (!tokens[*i] || !is_redirection(tokens[*i]))
		return (NULL);
	redir_token = tokens[*i];
	(*i)++;
	if (!tokens[*i])
		return (NULL);
	redir = create_ast_node(get_redir_type(redir_token));
	if (!redir)
		return (NULL);
	redir->filename = ft_strdup(tokens[*i]);
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
		redir->right = cmd;
		return (redir);
	}
	else
	{
		redir->left = cmd;
		return (redir);
	}
}

t_ast_node	*parse_cmd_with_redirections(char **tokens, int *i)
{
	t_ast_node	*cmd;
	t_ast_node	*redir;
	t_ast_node	*result;

	cmd = parse_simple_command(tokens, i);
	result = cmd;
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
