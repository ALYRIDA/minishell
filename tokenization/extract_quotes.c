/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:20:46 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/24 15:44:24 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_double_quotes(const char *s, int *i,
		char **envp, int in_single)
{
	int		start;
	char	*content;
	char	*expanded;

	(void)in_single;
	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	content = ft_substr_dup(s, start, *i - start);
	if (s[*i] == '"')
		(*i)++;
	if (ft_strlen(content) == 0)
	{
		free(content);
		return (ft_strdup("\x01"));  /* Marker for empty quoted string */
	}
	expanded = expand_variables(content, envp);
	free(content);
	return (expanded);
}

char	*extract_single_quotes(const char *s, int *i)
{
	int		start;
	char	*content;

	(*i)++; // skip opening '
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	content = ft_substr_dup(s, start, *i - start);
	if (s[*i] == '\'')
		(*i)++;
	if (ft_strlen(content) == 0)
	{
		free(content);
		return (ft_strdup("\x01"));  /* Marker for empty quoted string */
	}
	return (content);
}

int	check_unclosed_quotes(const char *s)
{
	int	i;
	int	single;
	int	dbl;

	i = 0;
	single = 0;
	dbl = 0;
	while (s[i])
	{
		if (s[i] == '\'' && dbl % 2 == 0)
			single++;
		else if (s[i] == '"' && single % 2 == 0)
			dbl++;
		i++;
	}
	if (single % 2 != 0)
		return (1); // unclosed single
	if (dbl % 2 != 0)
		return (2); // unclosed double
	return (0);
}
