/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/27 19:43:47 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **tokens, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0
		&& !is_redirection(tokens[i]))
	{
		count++;
		i++;
	}
	return (count);
}

static void	fill_args(char **tokens, int *i, char **args)
{
	int	j;

	j = 0;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0
		&& !is_redirection(tokens[*i]))
	{
		args[j] = ft_strdup(tokens[*i]);
		j++;
		(*i)++;
	}
	args[j] = NULL;
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
