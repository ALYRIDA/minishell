/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_resolver.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:00:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/05 19:29:39 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*try_path(char *dir, char *cmd)
{
	char	*path;
	int		dir_len;
	int		cmd_len;
	int		i;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	path = malloc(dir_len + cmd_len + 2);
	if (!path)
		return (NULL);
	i = 0;
	while (i < dir_len)
	{
		path[i] = dir[i];
		i++;
	}
	path[i++] = '/';
	while (*cmd)
		path[i++] = *cmd++;
	path[i] = '\0';
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

static char	*try_dir_path(char *path_env, int start, int i, char *cmd)
{
	char	*dir;
	char	*path;

	dir = extract_dir(path_env, start, i);
	if (!dir)
		return (NULL);
	path = try_path(dir, cmd);
	free(dir);
	return (path);
}

static char	*find_in_path(char *cmd, char **envp)
{
	char	*path_env;
	char	*path;
	int		i;
	int		start;

	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	i = 0;
	start = 0;
	while (1)
	{
		if (path_env[i] == ':' || path_env[i] == '\0')
		{
			path = try_dir_path(path_env, start, i, cmd);
			if (path)
				return (path);
			if (!path_env[i])
				break ;
			start = i + 1;
		}
		i++;
	}
	return (NULL);
}

char	*resolve_command_path(char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (find_in_path(cmd, envp));
}
