/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:49:19 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/18 18:39:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int	i;
	int	name_len;

	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen((char *)name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

int	ft_cd(char **argv, char ***envp)
{
	char	*value;
	char	*target;
	int		dir;

	if (!argv[1])
	{
		value = get_env_value(*envp, "HOME");
		if (!value)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
		target = value;
	}
	else
		target = argv[1];
	dir = chdir(target);
	if (dir == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	return (0);
}
