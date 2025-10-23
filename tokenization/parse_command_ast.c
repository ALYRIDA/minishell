/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:14:05 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/09 20:50:22 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1. Parse command arguments */
t_ast_node	*parse_command_args(char **tokens, int *i)
{
	t_ast_node	*node;
	int			j;

	node = create_node();
	node->type = AST_COMMAND;
	j = 0;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0
		&& ft_strcmp(tokens[*i], "<") != 0
		&& ft_strcmp(tokens[*i], ">") != 0
		&& ft_strcmp(tokens[*i], ">>") != 0
		&& ft_strcmp(tokens[*i], "<<") != 0)
	{
		node->argv = my_realloc(node->argv,
				sizeof(char *) * j, sizeof(char *) * (j + 2));
		node->argv[j] = ft_strdup(tokens[*i]);
		node->argv[j + 1] = NULL;
		j++;
		(*i)++;
	}
	return (node);
}

/* 2. Parse a single redirection */
t_ast_node	*parse_single_redirection(char **tokens, int *i)
{
	t_ast_node	*node;

	node = create_node();
	if (ft_strcmp(tokens[*i], "<") == 0)
		node->type = AST_REDIR_IN;
	else if (ft_strcmp(tokens[*i], ">") == 0)
		node->type = AST_REDIR_OUT;
	else if (ft_strcmp(tokens[*i], ">>") == 0)
		node->type = AST_REDIR_APPEND;
	else if (ft_strcmp(tokens[*i], "<<") == 0)
		node->type = AST_REDIR_HEREDOC;
	(*i)++;
	if (!tokens[*i])
	{
		printf("minishell: syntax error near unexpected token `newline`\n");
		free(node);
		return (NULL);
	}
	node->filename = ft_strdup(tokens[*i]);
	(*i)++;
	return (node);
}

/* Decide what kind of redirection this token is */
// *parse_redirection helper this is for the single_prase_redirection
t_ast_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (AST_REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (AST_REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (AST_REDIR_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (AST_REDIR_HEREDOC);
	return (AST_COMMAND);
}

/* 3. Collect all redirections for a command */
void	collect_redirections(t_ast_node *command, char **tokens, int *i)
{
	t_ast_node	*redir;
	t_ast_node	*last;

	last = command;
	while (tokens[*i] && (ft_strcmp(tokens[*i], "<") == 0
			|| ft_strcmp(tokens[*i], ">") == 0
			|| ft_strcmp(tokens[*i], ">>") == 0
			|| ft_strcmp(tokens[*i], "<<") == 0))
	{
		redir = parse_redirection(tokens, i);
		if (!redir)
			break ;
		last->right = redir;
		last = redir;
	}
}

/* 4. Full command parser */
t_ast_node	*parse_command(char **tokens, int *i)
{
	t_ast_node	*command;

	command = parse_command_args(tokens, i);
	collect_redirections(command, tokens, i);
	return (command);
}
