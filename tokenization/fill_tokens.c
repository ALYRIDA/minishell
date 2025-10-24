/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:05:52 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/24 15:41:11 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cleanup_tokens(char **tokens)
{
	int		count;
	char	**clean;

	count = count_valid_tokens(tokens);
	clean = malloc(sizeof(char *) * (count + 1));
	if (!clean)
		return (NULL);
	copy_valid_tokens(tokens, clean);
	free_tokens(tokens);
	return (clean);
}

static int	process_word_char(const char *s, int *i, char **envp,
		t_word_ctx *ctx)
{
	char	*part;

	if (s[*i] == '$' && (s[(*i) + 1] == '\'' || s[(*i) + 1] == '"'))//this to handle cases like $"" or $''
		(*i)++;
	else if (s[*i] == '"' && handle_double_quote(s, i, envp, ctx))
		return (1);
	else if (s[*i] == '\'' && handle_single_quote(s, i, ctx))
		return (1);
	else if (s[*i] != '"' && s[*i] != '\'')
	{
		part = extract_unquoted_part(s, i, envp);
		append_str(ctx->current, part, ctx->len);
		*ctx->had_content = 1;
		free(part);
	}
	return (0);
}

char	*extract_word(const char *s, int *i, char **envp)
{
	char		*current;
	int			len;
	int			had_content;
	t_word_ctx	ctx;

	current = ft_strdup("");
	len = 0;
	had_content = 0;
	ctx.current = &current;
	ctx.len = &len;
	ctx.had_content = &had_content;
	while (s[*i] && !isspace((unsigned char)s[*i])
		&& s[*i] != '|' && s[*i] != '<' && s[*i] != '>')
	{
		if (process_word_char(s, i, envp, &ctx))
			return (current);
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
