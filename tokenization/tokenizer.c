/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:34:19 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/15 14:54:35 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize(const char *s, char **envp)
{
	int		count;
	char	**tokens;

	count = count_tokens(s);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	fill_tokens(s, tokens, envp);
	tokens[count] = NULL;
	return (tokens);
}
