/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:40:19 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/23 14:09:21 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "<", 2)
		|| !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, "<<", 3)
		|| !ft_strncmp(token, ">>", 3))
		return (1);
	return (0);
}

static int	is_operator(char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "|", 2))
		return (1);
	return (is_redirect(token));
}

static void	print_syntax_error(char *token)
{
	if (!token)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (token && !ft_strncmp(token, "|", 2))
		printf("minishell: syntax error near unexpected token `|'\n");
	else
		printf("minishell: syntax error near unexpected token `%s'\n", token);
}

int	check_syntax(char **tokens)
{
	int	i;
	int	len;

	if (!tokens || !tokens[0])
		return (0);
	if (tokens[0] && !ft_strncmp(tokens[0], "|", 2))
		return (print_syntax_error(tokens[0]), 1);
	len = ft_tablen(tokens);
	if (is_operator(tokens[len - 1]))
		return (print_syntax_error(NULL), 1);
	i = 0;
	while (tokens[i])
	{
		if (is_operator(tokens[i]) && (!tokens[i + 1]
				|| is_operator(tokens[i + 1])))
			return (print_syntax_error(tokens[i + 1]), 1);
		i++;
	}
	return (0);
}
