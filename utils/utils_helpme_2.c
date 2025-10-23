/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:20:08 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/17 15:21:15 by aareslan         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		join[j++] = s2[i];
		i++;
	}
	join[j] = '\0';
	return (join);
}
