/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:45:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/05 19:30:03 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_env(char **envp)
{
	char	**sorted;
	int		i;
	int		len;

	len = 0;
	while (envp[len])
		len++;
	sorted = malloc(sizeof(char *) * (len + 1));
	if (!sorted)
		return ;
	i = 0;
	while (i < len)
	{
		sorted[i] = envp[i];
		i++;
	}
	sorted[len] = NULL;
	sort_env_array(sorted, len);
	i = 0;
	while (sorted[i])
	{
		print_sorted_entry(sorted[i]);
		i++;
	}
	free(sorted);
}

int	find_env_index(char **envp, char *var)
{
	int		i;
	int		var_len;
	int		j;

	j = 0;
	while (var[j] && var[j] != '=')
		j++;
	var_len = j;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, var_len) == 0
			&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**add_env_var(char **envp, char *var)
{
	char	**new_envp;
	int		len;
	int		i;

	(len = 0);
	while (envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (envp);
	i = 0;
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i++])
			return (free(new_envp), envp);
	}
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
		return (free(new_envp), envp);
	new_envp[i + 1] = NULL;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	return (free(envp), new_envp);
}

int	ft_export(char **argv, char ***envp)
{
	int		i;
	int		index;
	char	**new_envp;

	if (!argv[1])
		return (print_export_env(*envp), 0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
			return (write(2, "minishell: export: `", 20),
				write(2, argv[i], ft_strlen(argv[i])),
				write(2, "': not a valid identifier\n", 26), 1);
		index = find_env_index(*envp, argv[i]);
		if (index != -1 && ft_strchr(argv[i], '='))
			(free((*envp)[index]), (*envp)[index] = ft_strdup(argv[i]));
		else if (index == -1)
		{
			new_envp = add_env_var(*envp, argv[i]);
			if (new_envp != *envp)
				*envp = new_envp;
		}
		i++;
	}
	return (0);
}
