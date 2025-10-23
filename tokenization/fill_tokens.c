/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:05:52 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 18:02:40 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Check if token should be kept (not empty, or explicit empty quotes) */
static int	should_keep_token(const char *token)
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

char	**cleanup_tokens(char **tokens)
{
	int		count;
	int		i;
	char	**clean;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (should_keep_token(tokens[i]) || ft_strcmp(tokens[i], "\x01") == 0)
			count++;
		i++;
	}
	clean = malloc(sizeof(char *) * (count + 1));
	if (!clean)
		return (NULL);
	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "\x01") == 0)
			clean[count++] = ft_strdup("");  /* Convert marker to empty string */
		else if (should_keep_token(tokens[i]))
			clean[count++] = ft_strdup(tokens[i]);
		i++;
	}
	clean[count] = NULL;
	free_tokens(tokens);
	return (clean);
}

/* Extract unquoted portion that may contain $ for expansion */
static char	*extract_unquoted_part(const char *s, int *i, char **envp)
{
	int		start;
	int		j;
	char	*substr;
	char	*expanded;

	start = *i;
	j = *i;
	while (s[j] && s[j] != '\'' && s[j] != '"' && !isspace((unsigned char)s[j])
		&& s[j] != '|' && s[j] != '<' && s[j] != '>')
		j++;
	substr = ft_substr_dup(s, start, j - start);
	expanded = expand_variables(substr, envp);
	free(substr);
	*i = j;
	return (expanded);
}

char	*extract_word(const char *s, int *i, char **envp)
{
	char	*current;
	int		len;
	char	*part;
	int		had_content;

	current = ft_strdup("");
	len = 0;
	had_content = 0;
	while (s[*i] && !isspace((unsigned char)s[*i])
		&& s[*i] != '|' && s[*i] != '<' && s[*i] != '>')
	{
		if (s[*i] == '$' && (s[*i + 1] == '\'' || s[*i + 1] == '"'))
		{
			(*i)++;     //skip the dollar sign
			continue ;  //process quotes normally
		}
		if (s[*i] == '"')
		{
			part = extract_double_quotes(s, i, envp, 0);
			if (ft_strcmp(part, "\x01") == 0 && had_content == 0
				&& (isspace((unsigned char)s[*i]) || s[*i] == '\0'
					|| s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
			{
				free(current);
				return (part);  /* Return marker for empty quotes */
			}
			if (ft_strcmp(part, "\x01") != 0)
			{
				append_str(&current, part, &len);
				had_content = 1;
			}
			free(part);
		}
		else if (s[*i] == '\'')
		{
			part = extract_single_quotes(s, i);
			if (ft_strcmp(part, "\x01") == 0 && had_content == 0
				&& (isspace((unsigned char)s[*i]) || s[*i] == '\0'
					|| s[*i] == '|' || s[*i] == '<' || s[*i] == '>'))
			{
				free(current);
				return (part);  /* Return marker for empty quotes */
			}
			if (ft_strcmp(part, "\x01") != 0)
			{
				append_str(&current, part, &len);
				had_content = 1;
			}
			free(part);
		}
		else
		{
			part = extract_unquoted_part(s, i, envp);
			append_str(&current, part, &len);
			had_content = 1;
			free(part);
		}
	}
	return (current);
}

void	fill_tokens(const char *s, char **tokens, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (isspace((unsigned char)s[i]))
			i++;
		else if (s[i] == '|' || s[i] == '<' || s[i] == '>')
			tokens[j++] = extract_operator(s, &i);
		else
			tokens[j++] = extract_word(s, &i, envp);
	}
	tokens[j] = NULL;
}
