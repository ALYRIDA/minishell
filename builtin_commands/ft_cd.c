/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:49:19 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/06 21:41:20 by aareslan         ###   ########.fr       */
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

int	find_env_idx(char **envp, const char *name)
{
	int	i;
	int	name_len;

	name_len = ft_strlen((char *)name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	update_pwd_env(char ***envp, char *old_pwd, char *target)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		new_pwd = get_new_pwd_fallback(target, envp);
		if (!new_pwd)
			return ;
	}
	if (old_pwd)
		update_oldpwd(envp, old_pwd);
	update_current_pwd(envp, new_pwd);
	free(new_pwd);
}

static int	change_directory(char *target, char ***envp)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		free(old_pwd);
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	update_pwd_env(envp, old_pwd, target);
	free(old_pwd);
	return (0);
}

int	ft_cd(char **argv, char ***envp)
{
	char	*target;

	if (!argv[1])
	{
		if (handle_cd_home(*envp, &target) != 0)
			return (1);
	}
	else if (argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	else
		target = argv[1];
	return (change_directory(target, envp));
}
