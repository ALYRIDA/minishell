/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:00:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_dir(char *path_env, int start, int end)
{
	char	*dir;
	int		len;
	int		i;

	len = end - start;
	dir = malloc(len + 1);
	if (!dir)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dir[i] = path_env[start + i];
		i++;
	}
	dir[i] = '\0';
	return (dir);
}
