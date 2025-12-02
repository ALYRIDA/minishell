/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:30:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/20 15:40:48 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env_var(char ***envp, int index)
{
	int		i;
	int		len;
	char	**new_envp;

	len = 0;
	while ((*envp)[len])
		len++;
	new_envp = malloc(sizeof(char *) * len);
	if (!new_envp)
		return ;
	i = 0;
	while (i < index)
	{
		new_envp[i] = (*envp)[i];
		i++;
	}
	free((*envp)[index]);
	while (i < len - 1)
	{
		new_envp[i] = (*envp)[i + 1];
		i++;
	}
	new_envp[i] = NULL;
	free(*envp);
	*envp = new_envp;
}

int	find_env_var(char **envp, char *var)
{
	int	i;
	int	var_len;

	if (!var)
		return (-1);
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unset(char **args, char ***envp)
{
	int	i;
	int	index;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		index = find_env_var(*envp, args[i]);
		if (index != -1)
			remove_env_var(envp, index);
		i++;
	}
	return (0);
}
