/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:00:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/24 15:41:53 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_empty_quote_marker(char *part, int had_content, const char *s, int i)
{
	if (ft_strcmp(part, "\x01") != 0)
		return (0);
	if (had_content != 0)
		return (0);
	if (isspace((unsigned char)s[i]) || s[i] == '\0'
		|| s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (1);
	return (0);
}

int	handle_double_quote(const char *s, int *i, char **envp, t_word_ctx *ctx)
{
	char	*part;

	part = extract_double_quotes(s, i, envp, 0);
	if (is_empty_quote_marker(part, *ctx->had_content, s, *i))
	{
		free(*ctx->current);
		*ctx->current = part;
		return (1);
	}
	if (ft_strcmp(part, "\x01") != 0)
	{
		append_str(ctx->current, part, ctx->len);
		*ctx->had_content = 1;
	}
	free(part);
	return (0);
}

int	handle_single_quote(const char *s, int *i, t_word_ctx *ctx)
{
	char	*part;

	part = extract_single_quotes(s, i);
	if (is_empty_quote_marker(part, *ctx->had_content, s, *i))
	{
		free(*ctx->current);
		*ctx->current = part;
		return (1);
	}
	if (ft_strcmp(part, "\x01") != 0)
	{
		append_str(ctx->current, part, ctx->len);
		*ctx->had_content = 1;
	}
	free(part);
	return (0);
}

char	*extract_unquoted_part(const char *s, int *i, char **envp)
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
