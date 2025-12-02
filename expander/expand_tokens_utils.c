/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:00:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_total_tokens(char **tokens)
{
	int	total_count;
	int	i;

	total_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (should_split_token(tokens[i]))
			total_count += count_words_in_token(tokens[i]);
		else
			total_count++;
		i++;
	}
	return (total_count);
}

void	add_split_tokens(char **result, int *k, char *token)
{
	char	**split_words;
	int		j;

	split_words = split_token_by_spaces(token);
	j = 0;
	while (split_words && split_words[j])
	{
		result[*k] = split_words[j];
		(*k)++;
		j++;
	}
	free(split_words);
}

int	has_quote_marker(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\x02' || token[i] == '\x01')
			return (1);
		i++;
	}
	return (0);
}
