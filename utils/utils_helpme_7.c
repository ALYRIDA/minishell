/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:21 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/11 21:23:48 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_environment(char **envp)
{
	char	**new_envp;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	free_environment(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	handle_syntax_error(char **tokens)
{
	if (tokens && check_syntax(tokens))
	{
		free_tokens(tokens);
		return (1);
	}
	return (0);
}
