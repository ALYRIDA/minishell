/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:21:57 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 14:38:41 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**expand_tokens(char **tokens, char **envp)
{
	int		i;
	char	**res;

	(void)envp;
	res = malloc(sizeof(char *) * (ft_tablen(tokens) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		res[i] = ft_strdup(tokens[i]);
		i++;
	}
	res[i] = NULL;
	free_tokens(tokens);
	return (res);
}
