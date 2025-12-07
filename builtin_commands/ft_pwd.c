/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:43:31 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/06 15:45:01 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_pwd(char **envp)
{
	int	i;
	int	name_len;

	if (!envp)
		return (NULL);
	name_len = 3;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD", name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

int	ft_pwd(char **envp)
{
	char	*cwd;
	char	*env_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		env_pwd = get_env_pwd(envp);
		if (env_pwd)
		{
			write(1, env_pwd, ft_strlen(env_pwd));
			write(1, "\n", 1);
			return (0);
		}
		write(2, "pwd: error retrieving current directory\n", 40);
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (0);
}
