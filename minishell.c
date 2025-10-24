/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:06 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/23 18:17:11 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *input, char **envp)
{
	char	**tokens;

	if (*input)
	{
		add_history(input);
		if (check_quotes(input))
			return ;
		tokens = tokenize(input, envp);
		tokens = cleanup_tokens(tokens);
		if (tokens && check_syntax(tokens))
		{
			free_tokens(tokens);
			return ;
		}
		if (tokens)
		{
			tokens = expand_tokens(tokens, envp);
			display_tokens(tokens);
			free_tokens(tokens);
		}
	}
}

static int	handle_exit(char *input)
{
	if (!input)
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

static void	run_shell_loop(char **envp)
{
	char	*input;

	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (handle_exit(input))
			break ;
		process_input(input, envp);
		if (get_signal() == SIGINT)
			reset_signal();
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		run_shell_loop(envp);
	return (0);
}
