/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:40:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/24 00:54:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

int	handle_syntax_error(char **tokens)
{
	if (tokens && check_syntax(tokens))
	{
		set_exit_status(2);
		free_tokens(tokens);
		return (1);
	}
	return (0);
}

void	process_tokens(char **tokens, char ***envp)
{
	t_ast_node	*ast;

	if (tokens)
	{
		tokens = expand_tokens(tokens, *envp);
		ast = parse_tokens(tokens);
		if (ast)
		{
			set_exit_status(execute_ast(ast, envp));
			free_ast(ast);
		}
		free_tokens(tokens);
	}
}
