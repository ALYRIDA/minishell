/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:06 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/09 12:32:12 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_syntax_error(char **tokens)
{
	if (tokens && check_syntax(tokens))
	{
		free_tokens(tokens);
		return (1);
	}
	return (0);
}

void	process_input(char *input, char ***envp)
{
	char		**tokens;
	t_ast_node	*ast;

	if (*input)
	{
		add_history(input);
		if (check_quotes(input))
			return ;
		tokens = tokenize(input, *envp);
		tokens = cleanup_tokens(tokens);
		if (handle_syntax_error(tokens))
			return ;
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
}

int	handle_exit(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

void	ft_minishell(char **envp)
{
	char	*input;
	char	**local_envp;

	local_envp = copy_environment(envp);
	if (!local_envp)
	{
		printf("Error: Failed to copy environment\n");
		return ;
	}
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (handle_exit(input))
			break ;
		process_input(input, &local_envp);
		if (get_signal() == SIGINT)
			reset_signal();
		free(input);
	}
	free_environment(local_envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		ft_minishell(envp);
	return (0);
}
