/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:21 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_num_len(int n)
{
	int	len;
	int	num;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	num = n;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static char	*ft_itoa_shlvl(int n)
{
	char	*str;
	int		len;

	len = get_num_len(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	while (n)
	{
		if (n > 0)
			str[--len] = n % 10 + '0';
		else
			str[--len] = -n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static char	*create_shlvl_var(int level)
{
	char	*level_str;
	char	*result;
	int		i;
	int		j;

	level_str = ft_itoa_shlvl(level);
	if (!level_str)
		return (NULL);
	result = malloc(6 + ft_strlen(level_str) + 1);
	if (!result)
		return (free(level_str), NULL);
	i = 0;
	while ("SHLVL="[i])
	{
		result[i] = "SHLVL="[i];
		i++;
	}
	j = 0;
	while (level_str[j])
		result[i++] = level_str[j++];
	result[i] = '\0';
	free(level_str);
	return (result);
}

static int	is_shlvl_entry(char *env_entry)
{
	if (ft_strlen(env_entry) > 6 && env_entry[0] == 'S'
		&& env_entry[1] == 'H' && env_entry[2] == 'L'
		&& env_entry[3] == 'V' && env_entry[4] == 'L' && env_entry[5] == '=')
		return (1);
	return (0);
}

int	increment_shlvl_in_env(char **envp)
{
	int		i;
	int		current_level;
	char	*new_shlvl;

	i = 0;
	while (envp[i])
	{
		if (is_shlvl_entry(envp[i]))
		{
			current_level = ft_atoi_shlvl(envp[i] + 6);
			new_shlvl = create_shlvl_var(current_level + 1);
			if (!new_shlvl)
				return (0);
			free(envp[i]);
			envp[i] = new_shlvl;
			return (1);
		}
		i++;
	}
	return (0);
}
