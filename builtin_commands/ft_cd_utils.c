/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:31:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/06 21:41:20 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*build_new_pwd_relative(char *old_pwd_value, char *target)
{
	char	*new_pwd;
	int		old_len;
	int		target_len;

	old_len = ft_strlen(old_pwd_value);
	target_len = ft_strlen(target);
	new_pwd = malloc(old_len + target_len + 2);
	if (new_pwd)
	{
		ft_memcpy(new_pwd, old_pwd_value, old_len);
		new_pwd[old_len] = '/';
		ft_memcpy(new_pwd + old_len + 1, target, target_len + 1);
	}
	return (new_pwd);
}

char	*get_new_pwd_fallback(char *target, char ***envp)
{
	char	*old_pwd_value;
	char	*new_pwd;

	old_pwd_value = get_env_value(*envp, "PWD");
	if (old_pwd_value && target[0] != '/')
		new_pwd = build_new_pwd_relative(old_pwd_value, target);
	else if (target[0] == '/')
		new_pwd = ft_strdup(target);
	else
		new_pwd = NULL;
	return (new_pwd);
}

void	update_oldpwd(char ***envp, char *old_pwd)
{
	char	*env_str;
	int		idx;

	env_str = malloc(ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1);
	if (env_str)
	{
		ft_memcpy(env_str, "OLDPWD=", 7);
		ft_memcpy(env_str + 7, old_pwd, ft_strlen(old_pwd) + 1);
		idx = find_env_idx(*envp, "OLDPWD");
		if (idx != -1)
			(free((*envp)[idx]), (*envp)[idx] = env_str);
		else
			free(env_str);
	}
}

void	update_current_pwd(char ***envp, char *new_pwd)
{
	char	*env_str;
	int		idx;

	env_str = malloc(ft_strlen("PWD=") + ft_strlen(new_pwd) + 1);
	if (env_str)
	{
		ft_memcpy(env_str, "PWD=", 4);
		ft_memcpy(env_str + 4, new_pwd, ft_strlen(new_pwd) + 1);
		idx = find_env_idx(*envp, "PWD");
		if (idx != -1)
			(free((*envp)[idx]), (*envp)[idx] = env_str);
		else
			free(env_str);
	}
}

int	handle_cd_home(char **envp, char **target)
{
	char	*value;

	value = get_env_value(envp, "HOME");
	if (!value)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	*target = value;
	return (0);
}
