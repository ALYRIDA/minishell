/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/27 19:43:45 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*parse_pipeline(char **tokens)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;
	int			i;

	i = 0;
	left = parse_cmd_with_redirections(tokens, &i);
	if (!left)
		return (NULL);
	while (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
	{
		i++;
		if (!tokens[i])
			return (free_ast(left), NULL);
		pipe_node = create_ast_node(AST_PIPE);
		if (!pipe_node)
			return (free_ast(left), NULL);
		pipe_node->left = left;
		pipe_node->right = parse_cmd_with_redirections(tokens, &i);
		if (!pipe_node->right)
			return (free_ast(pipe_node), NULL);
		left = pipe_node;
	}
	return (left);
}
