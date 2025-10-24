/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:24:28 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/24 15:16:34 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Handle special variables like $$, $@, $*, $#, $1-$9, etc. */
static void	handle_special_var(char *input, int *i, t_expand_ctx *ctx)
{
	char	*pid_str;

	if (input[*i + 1] == '$')
	{
		pid_str = ft_itoa(ft_getpid());
		if (pid_str)
		{
			append_str(ctx->res, pid_str, ctx->len);
			free(pid_str);
		}
		(*i) += 2;
		return ;
	}
	if (input[*i + 1] == '@' || input[*i + 1] == '*'
		|| input[*i + 1] == '#' || ft_isdigit(input[*i + 1]))
		(*i) += 2;
	else
		append_char(ctx->res, input[(*i)++], ctx->len);
}

/* Handle environment variable expansion */
static void	handle_env_var(char *input, int *i, t_expand_ctx *ctx)
{
	char	*name;
	char	*value;

	name = get_var_name(input, i);
	if (!name)
		return ;
	value = getenv_value(ctx->envp, name);
	if (value)
		append_str(ctx->res, value, ctx->len);
	free(name);
}

/* Handle $VAR or $? or special variables */
void	handle_dollar(char *input, int *i, t_expand_ctx *ctx)
{
	if (input[*i + 1] == '\'' || input[*i + 1] == '"')
		return ((void)((*i)++));
	if (input[*i + 1] == '?')
	{
		expand_exit_code(ctx->res, ctx->len, i);
		return ;
	}
	if (input[*i + 1] == '$' || input[*i + 1] == '@'
		|| input[*i + 1] == '*' || input[*i + 1] == '#'
		|| ft_isdigit(input[*i + 1]))
	{
		handle_special_var(input, i, ctx);
		return ;
	}
	if (!ft_isalnum(input[*i + 1]) && input[*i + 1] != '_')
	{
		append_char(ctx->res, input[(*i)++], ctx->len);
		return ;
	}
	handle_env_var(input, i, ctx);
}
