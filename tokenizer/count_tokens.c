/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:05:06 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/15 14:54:03 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator(const char *s, int *i)
{
	skip_operator(s, i);
	return (1);
}

int	handle_quotes(const char *s, int *i)
{
	skip_quotes(s, i);
	return (1);
}

int	handle_word(const char *s, int *i)
{
	skip_word(s, i);
	return (1);
}

int	count_tokens(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (isspace((unsigned char)s[i]))
			i++;
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			count += handle_operator(s, &i);
		else if (s[i] == '"' || s[i] == '\'')
			count += handle_quotes(s, &i);
		else
			count += handle_word(s, &i);
	}
	return (count);
}
