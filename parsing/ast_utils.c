/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/27 19:43:47 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ast_type(t_ast_type type)
{
	if (type == AST_COMMAND)
		printf("COMMAND");
	else if (type == AST_PIPE)
		printf("PIPE");
	else if (type == AST_REDIR_IN)
		printf("REDIR_IN");
	else if (type == AST_REDIR_OUT)
		printf("REDIR_OUT");
	else if (type == AST_REDIR_APPEND)
		printf("REDIR_APPEND");
	else if (type == AST_REDIR_HEREDOC)
		printf("REDIR_HEREDOC");
}

static void	print_ast_helper(t_ast_node *node, int depth)
{
	int	i;
	int	j;

	if (!node)
		return ;
	j = 0;
	while (j < depth)
	{
		printf("  ");
		j++;
	}
	print_ast_type(node->type);
	if (node->type == AST_COMMAND && node->args)
	{
		printf(": ");
		i = 0;
		while (node->args[i])
		{
			printf("%s", node->args[i]);
			if (node->args[i + 1])
				printf(" ");
			i++;
		}
	}
	else if (node->filename)
		printf(" -> %s", node->filename);
	printf("\n");
	if (node->left)
		print_ast_helper(node->left, depth + 1);
	if (node->right)
		print_ast_helper(node->right, depth + 1);
}

void	print_ast(t_ast_node *node)
{
	printf("AST Structure:\n");
	print_ast_helper(node, 0);
}
