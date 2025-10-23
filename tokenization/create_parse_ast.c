/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parse_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:44:34 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 15:14:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1. Create and initialize a new AST node */
t_ast_node	*create_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_COMMAND;
	node->argv = NULL;
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* Parse one redirection safely */
t_ast_node	*parse_redirection(char **tokens, int *i)
{
	t_ast_node	*node;

	node = create_node();
	if (!node)
		return (NULL);
	node->type = get_redir_type(tokens[*i]);
	(*i)++;
	if (tokens[*i])
	{
		node->filename = ft_strdup(tokens[*i]);
		(*i)++;
	}
	else
	{
		printf("minishell: syntax error near unexpected token `newline`\n");
		free(node);
		return (NULL);
	}
	return (node);
}

// /* helper: create a pipe node */
// t_ast_node	*make_pipe_node(t_ast_node *left, char **tokens, int *i)
// {
// 	t_ast_node	*node;

// 	node = create_node();
// 	node->type = AST_PIPE;
// 	node->left = left;
// 	(*i)++;
// 	node->right = parse_pipe(tokens, i);
// 	return (node);
// }

// /* 3. Parse pipe recursively */
// t_ast_node	*parse_pipe(char **tokens, int *i)
// {
// 	t_ast_node	*left;

// 	left = parse_command(tokens, i);
// 	if (tokens[*i] && ft_strcmp(tokens[*i], "|") == 0)
// 		return (make_pipe_node(left, tokens, i));
// 	return (left);
// }

// /* 4. Main AST parser */
// t_ast_node	*parse_ast(char **tokens)
// {
// 	int			i;
// 	t_ast_node	*root;

// 	i = 0;
// 	root = parse_pipe(tokens, &i);
// 	return (root);
// }
