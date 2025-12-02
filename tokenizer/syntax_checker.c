/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:40:19 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirect(char *token)
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

int	is_operator(char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "|", 2))
		return (1);
	return (is_redirect(token));
}

void	print_syntax_error(char *token)
{
	if (!token)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token `newline'\n", 27);
	}
	else if (token && !ft_strncmp(token, "|", 2))
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	else
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, token, ft_strlen(token));
		write(2, "'\n", 2);
	}
}

static int	check_token_syntax(char **tokens, int i)
{
	if (!ft_strncmp(tokens[i], "|", 2))
	{
		if (!tokens[i + 1] || !ft_strncmp(tokens[i + 1], "|", 2))
			return (print_syntax_error(tokens[i + 1]), 1);
	}
	else if (is_redirect(tokens[i]))
	{
		if (!tokens[i + 1] || is_operator(tokens[i + 1]))
			return (print_syntax_error(tokens[i + 1]), 1);
	}
	return (0);
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
		if (check_token_syntax(tokens, i) != 0)
			return (1);
		i++;
	}
	return (0);
}
