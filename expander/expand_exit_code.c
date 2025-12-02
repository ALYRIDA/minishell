/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:30:08 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/19 13:56:10 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exit_code(char **res, int *len, int *i)
{
	char	*exit_code;

	(*i) += 2;
	exit_code = ft_itoa(get_exit_status());
	if (!exit_code)
		return ;
	append_str(res, exit_code, len);
	free(exit_code);
}
