/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:30:47 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/06 21:41:20 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expand_ctx(t_expand_ctx *ctx, char **res, int *len,
			char **envp)
{
	ctx->res = res;
	ctx->len = len;
	ctx->envp = envp;
}

static void	process_char(char *input, int *i, t_expand_ctx *ctx)
{
	if (input[*i] == '\\' && input[*i + 1])
	{
		append_char(ctx->res, input[*i + 1], ctx->len);
		*i += 2;
	}
	else if (input[*i] == '$')
		handle_dollar(input, i, ctx);
	else
		append_char(ctx->res, input[(*i)++], ctx->len);
}

/* Expand variables in string */
char	*expand_variables(char *input, char **envp)
{
	int				i;
	int				len;
	char			*res;
	t_expand_ctx	ctx;

	i = 0;
	len = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	init_expand_ctx(&ctx, &res, &len, envp);
	while (input[i])
		process_char(input, &i, &ctx);
	return (res);
}
