/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:20:46 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/12 11:05:14 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mark_quoted_str(char *expanded)
{
	char	*marked;

	marked = malloc(ft_strlen(expanded) + 2);
	if (!marked)
		return (expanded);
	marked[0] = '\x02';
	strcpy(marked + 1, expanded);
	free(expanded);
	return (marked);
}

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
		return (free(content), ft_strdup("\x01"));
	expanded = expand_variables(content, envp);
	free(content);
	return (mark_quoted_str(expanded));
}

char	*extract_single_quotes(const char *s, int *i)
{
	int		start;
	char	*content;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	content = ft_substr_dup(s, start, *i - start);
	if (s[*i] == '\'')
		(*i)++;
	if (ft_strlen(content) == 0)
		return (free(content), ft_strdup("\x01"));
	return (mark_quoted_str(content));
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
		return (1);
	if (dbl % 2 != 0)
		return (2);
	return (0);
}
