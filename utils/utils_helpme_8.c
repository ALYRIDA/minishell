/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helpme_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:08:16 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/18 17:08:18 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Strips the quote marker (\x02) from a string
 * Returns a newly allocated string without the marker
 */
char	*strip_quote_marker(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\x02')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

/**
 * Strips quote markers from all arguments in place
 * This should be called after parsing and before execution
 */
void	strip_markers_from_args(char **args)
{
	int		i;
	char	*cleaned;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		cleaned = strip_quote_marker(args[i]);
		if (cleaned)
		{
			free(args[i]);
			args[i] = cleaned;
		}
		i++;
	}
}