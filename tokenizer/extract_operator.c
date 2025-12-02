/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:04:51 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/14 10:35:07 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_operator(const char *s, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 1;
	if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
	{
		len = 2;
		(*i)++;
	}
	(*i)++;
	return (ft_substr_dup(s, start, len));
}
