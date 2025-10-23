/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:31:51 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/14 09:24:18 by aareslan         ###   ########.fr       */
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
