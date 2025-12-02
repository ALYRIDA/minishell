/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:20:08 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/09 11:20:40 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_operator(const char *s, int *i)
{
	if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
		(*i)++;
	(*i)++;
	return (1);
}

int	skip_quotes(const char *s, int *i)
{
	char	quote;

	quote = s[(*i)++];
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

int	skip_word(const char *s, int *i)
{
	while (s[*i] && !isspace((unsigned char)s[*i])
		&& s[*i] != '|' && s[*i] != '<' && s[*i] != '>'
		&& s[*i] != '"' && s[*i] != '\'')
		(*i)++;
	return (1);
}
