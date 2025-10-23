/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:30:08 by aareslan          #+#    #+#             */
/*   Updated: 2025/09/14 16:16:06 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exit_code(char **res, int *len, int *i)
{
	char	*exit_code;

	(*i) += 2; // consume "$?"
	exit_code = ft_itoa(g_signal);
	if (!exit_code)
		return ;
	append_str(res, exit_code, len);
	free(exit_code);
}
