/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:06 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 14:38:45 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *input, char **envp)
{
	char	**tokens;
	int		i;
	int		quote_status;

	if (*input)
	{
		quote_status = check_unclosed_quotes(input);
		if (quote_status == 1)
		{
			printf("minishell: syntax error: unclosed single quote\n");
			return ;
		}
		else if (quote_status == 2)
		{
			printf("minishell: syntax error: unclosed double quote\n");
			return ;
		}
		add_history(input);
		tokens = tokenize(input, envp);
		tokens = cleanup_tokens(tokens);
		if (tokens)
		{
			tokens = expand_tokens(tokens, envp);
			i = 0;
			while (tokens[i])
			{
				printf("[%d]: %s\n", i, tokens[i]);
				i++;
			}
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
