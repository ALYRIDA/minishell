/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args_after_redir(char **tokens, int i)
{
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		if (is_redirection(tokens[i]))
		{
			i += 2;
			if (tokens[i] && !is_redirection(tokens[i])
				&& ft_strcmp(tokens[i], "|") != 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

t_ast_node	*parse_command_redirections(char **tokens, int *i)
{
	t_ast_node	*cmd;
	int			arg_count;
	int			start;

	if (!tokens[*i] || ft_strcmp(tokens[*i], "|") == 0)
		return (NULL);
	if (is_redirection(tokens[*i]))
		return (NULL);
	if (!check_args_after_redir(tokens, *i))
		return (NULL);
	start = *i;
	arg_count = count_args_with_redirections(tokens, start);
	if (arg_count == 0)
		return (NULL);
	cmd = create_ast_node(AST_COMMAND);
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (free_ast(cmd), NULL);
	*i = start;
	fill_args_with_redirections(tokens, i, cmd->args);
	return (cmd);
}

t_ast_node	*parse_simple_command(char **tokens, int *i)
{
	t_ast_node	*cmd;
	int			arg_count;
	int			start;

	if (!tokens[*i] || ft_strcmp(tokens[*i], "|") == 0
		|| is_redirection(tokens[*i]))
		return (NULL);
	cmd = create_ast_node(AST_COMMAND);
	if (!cmd)
		return (NULL);
	start = *i;
	arg_count = count_args(tokens, start);
	if (arg_count == 0)
		return (free_ast(cmd), NULL);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (free_ast(cmd), NULL);
	*i = start;
	fill_args(tokens, i, cmd->args);
	return (cmd);
}
