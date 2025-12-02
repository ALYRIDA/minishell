/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_default_cmd(char **tokens, int i)
{
	t_ast_node	*result;

	result = create_ast_node(AST_COMMAND);
	if (!result)
		return (NULL);
	result->args = malloc(sizeof(char *) * 2);
	if (!result->args)
		return (free_ast(result), NULL);
	if (tokens[i] && ft_strcmp(tokens[i], "<<") == 0)
	{
		result->args[0] = ft_strdup(":");
		result->args[1] = NULL;
		return (result);
	}
	result->args[0] = ft_strdup("");
	if (!result->args[0])
		return (free_ast(result), NULL);
	result->args[1] = NULL;
	return (result);
}
