/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:31:23 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/14 09:24:09 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Get variable name after $ */
char	*get_var_name(char *s, int *i)
{
	int		start;
	int		len;
	char	*name;

	(*i)++;
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	len = *i - start;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_memcpy(name, s + start, len);
	name[len] = '\0';
	return (name);
}
