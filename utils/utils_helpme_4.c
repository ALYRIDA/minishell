/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:34:55 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/22 14:50:50 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;	

	i = 0;
	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (int)str[i] - '0';
		i++;
	}
	return (sign * result);
}

int	is_explicit_empty(const char *s)
{
	return (s && ((s[0] == '\'' && s[1] == '\'' && s[2] == '\0')
			|| (s[0] == '"' && s[1] == '"' && s[2] == '\0')));
}

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	if (!tab)
		return (0);
	while (tab[len])
		len++;
	return (len);
}
