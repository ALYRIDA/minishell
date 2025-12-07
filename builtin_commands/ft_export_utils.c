/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:00:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/12/03 21:00:10 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_sorted_entry(char *entry)
{
	int	j;

	write(1, "declare -x ", 11);
	j = 0;
	while (entry[j] && entry[j] != '=')
		(write(1, &entry[j], 1), j++);
	if (entry[j] == '=')
	{
		(write(1, "=\"", 2), j++);
		while (entry[j])
			(write(1, &entry[j], 1), j++);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	sort_env_array(char **sorted, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
