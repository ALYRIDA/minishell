/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:44:09 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/21 09:57:27 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Append a single character */
void	append_char(char **res, char c, int *len)
{
	char	*new_res;
	int		i;

	new_res = malloc(*len + 2);
	if (!new_res)
		return ;
	i = 0;
	while (i < *len)
	{
		new_res[i] = (*res)[i];
		i++;
	}
	new_res[i] = c;
	new_res[i + 1] = '\0';
	free(*res);
	*res = new_res;
	(*len)++;
}

void	append_str(char **res, char *str, int *len)
{
	int		slen;
	int		i;
	char	*new_res;

	if (!str)
		return ;
	slen = ft_strlen(str);
	new_res = malloc(*len + slen + 1);
	if (!new_res)
		return ;
	i = 0;
	while (i < *len)
	{
		new_res[i] = (*res)[i];
		i++;
	}
	ft_memcpy(new_res + i, str, slen);
	new_res[i + slen] = '\0';
	free(*res);
	*res = new_res;
	*len += slen;
}
