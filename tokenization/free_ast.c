/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:30:52 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 14:58:57 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1. Free argv array */
void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/* 2. Free single node (no recursion) */
void	free_node_content(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->argv)
		free_argv(node->argv);
	if (node->filename)
		free(node->filename);
}

/* 3. Recursive free */
void	free_ast_recursive(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast_recursive(node->left);
	if (node->right)
		free_ast_recursive(node->right);
	free_node_content(node);
	free(node);
}

/* 4. Public function */
void	free_ast(t_ast_node *root)
{
	free_ast_recursive(root);
}
