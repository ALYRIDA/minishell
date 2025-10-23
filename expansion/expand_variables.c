/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:30:47 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/21 13:17:08 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ctx.res = &res;
	ctx.len = &len;
	ctx.envp = envp;
	while (input[i])
	{
		if (input[i] == '$')
			handle_dollar(input, &i, &ctx);
		else
			append_char(&res, input[i++], &len);
	}
	return (res);
}
