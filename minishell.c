/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:06 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/06 21:56:22 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, char ***envp)
{
	char		**tokens;

	if (*input)
	{
		add_history(input);
		if (check_quotes(input))
		{
			set_exit_status(2);
			return ;
		}
		tokens = tokenize(input, *envp);
		tokens = cleanup_tokens(tokens);
		if (handle_syntax_error(tokens))
			return ;
		process_tokens(tokens, envp);
	}
}

static void	handle_signal_check(void)
{
	if (get_signal() == SIGINT)
	{
		set_exit_status(130);
		reset_signal();
	}
}

static void	main_loop(char ***local_envp)
{
	char	*input;

	while (1)
	{
		input = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (handle_exit(input))
			break ;
		process_input(input, local_envp);
		if (get_exit_status() == 130)
		{
			free(input);
			continue ;
		}
		handle_signal_check();
		free(input);
	}
}

void	ft_minishell(char **envp)
{
	char	**local_envp;

	local_envp = copy_environment_with_incremented_shlvl(envp);
	if (!local_envp)
	{
		printf("Error: Failed to copy environment\n");
		return ;
	}
	print_welcome_banner();
	setup_signals();
	main_loop(&local_envp);
	rl_clear_history();
	free_environment(local_envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		ft_minishell(envp);
	return (0);
}
