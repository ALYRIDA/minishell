/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:00:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/02 21:32:06 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi_shlvl(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

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

void	increment_shlvl(char **envp)
{
	increment_shlvl_in_env(envp);
}

static char	**add_shlvl_to_env(char **new_envp)
{
	char	**temp;
	int		len;
	int		i;

	len = 0;
	while (new_envp[len])
		len++;
	temp = malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return (free_environment(new_envp), NULL);
	i = -1;
	while (++i < len)
		temp[i] = new_envp[i];
	temp[len] = ft_strdup("SHLVL=1");
	temp[len + 1] = NULL;
	free(new_envp);
	return (temp);
}

char	**copy_environment_with_incremented_shlvl(char **envp)
{
	char	**new_envp;
	int		result;

	new_envp = copy_environment(envp);
	if (!new_envp)
		return (NULL);
	result = increment_shlvl_in_env(new_envp);
	if (result == 0)
		return (add_shlvl_to_env(new_envp));
	return (new_envp);
}
