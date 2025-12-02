/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:31:51 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/19 13:56:25 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Return variable value from envp */
char	*getenv_value(char **envp, char *name)
{
	int	len;
	int	j;

	len = ft_strlen(name);
	j = 0;
	while (envp && envp[j])
	{
		if (!ft_strncmp(envp[j], name, len) && envp[j][len] == '=')
			return (envp[j] + len + 1);
		j++;
	}
	return ("");
}
