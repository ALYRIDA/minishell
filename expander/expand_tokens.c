/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:21:57 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_in_token(char *token)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (token[i])
	{
		if (isspace((unsigned char)token[i]))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	should_split_token(char *token)
{
	int	i;

	if (has_quote_marker(token))
		return (0);
	i = 0;
	while (token[i])
	{
		if (isspace((unsigned char)token[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**split_token_by_spaces(char *token)
{
	char	**words;
	int		count;
	int		i;
	int		j;
	int		start;

	count = count_words_in_token(token);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		while (token[i] && isspace((unsigned char)token[i]))
			i++;
		start = i;
		while (token[i] && !isspace((unsigned char)token[i]))
			i++;
		if (i > start)
			words[j++] = ft_substr_dup(token, start, i - start);
	}
	words[j] = NULL;
	return (words);
}

static char	**expand_and_split_tokens(char **tokens)
{
	char	**result;
	int		i;
	int		k;
	int		total_count;

	total_count = count_total_tokens(tokens);
	result = malloc(sizeof(char *) * (total_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (tokens[i])
	{
		if (should_split_token(tokens[i]))
			add_split_tokens(result, &k, tokens[i]);
		else
			result[k++] = ft_strdup(tokens[i]);
		i++;
	}
	result[k] = NULL;
	return (result);
}

char	**expand_tokens(char **tokens, char **envp)
{
	char	**res;

	(void)envp;
	res = expand_and_split_tokens(tokens);
	free_tokens(tokens);
	return (res);
}
