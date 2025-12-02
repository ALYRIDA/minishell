/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:50:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_with_redirections(char **tokens, int start)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		if (is_redirection(tokens[i]))
		{
			i += 2;
			if (!tokens[i])
				break ;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	count_args(char **tokens, int start)
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

static void	collect_args_skip_redir(char **tokens, int *orig_i, char **args,
		int *j)
{
	while (tokens[*orig_i] && ft_strcmp(tokens[*orig_i], "|") != 0)
	{
		if (is_redirection(tokens[*orig_i]))
		{
			*orig_i += 2;
			if (!tokens[*orig_i])
				break ;
		}
		else
		{
			args[*j] = ft_strdup(tokens[*orig_i]);
			(*j)++;
			(*orig_i)++;
		}
	}
}

void	fill_args_with_redirections(char **tokens, int *i, char **args)
{
	int	j;
	int	orig_i;

	j = 0;
	orig_i = *i;
	collect_args_skip_redir(tokens, &orig_i, args, &j);
	args[j] = NULL;
	while (tokens[*i] && ft_strcmp(tokens[*i], "|") != 0
		&& !is_redirection(tokens[*i]))
		(*i)++;
	if (ft_strcmp(tokens[*i], "|") == 0 || !tokens[*i])
		*i = orig_i;
}

void	fill_args(char **tokens, int *i, char **args)
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
