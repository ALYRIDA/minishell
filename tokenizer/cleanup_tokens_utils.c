/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/23 18:17:09 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	should_keep_token(const char *token)
{
	int	len;

	if (!token)
		return (0);
	len = ft_strlen(token);
	if (len == 0)
		return (0);
	if (len >= 2 && ((token[0] == '\'' && token[len - 1] == '\'')
			|| (token[0] == '"' && token[len - 1] == '"')))
		return (1);
	if (token[0] != '\0')
		return (1);
	return (0);
}

int	count_valid_tokens(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (should_keep_token(tokens[i]) || ft_strcmp(tokens[i], "\x01") == 0)
			count++;
		i++;
	}
	return (count);
}

void	copy_valid_tokens(char **tokens, char **clean)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "\x01") == 0)
			clean[count++] = ft_strdup("");
		else if (should_keep_token(tokens[i]))
			clean[count++] = ft_strdup(tokens[i]);
		i++;
	}
	clean[count] = NULL;
}
