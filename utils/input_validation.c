/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:30:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/23 18:17:10 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input)
{
	int		quote_err;
	char	*msg;

	quote_err = check_unclosed_quotes(input);
	if (quote_err)
	{
		msg = "minishell: unexpected EOF ";
		write(2, msg, ft_strlen(msg));
		if (quote_err == 1)
			msg = "while looking for matching `''\n";
		else
			msg = "while looking for matching `\"'\n";
		write(2, msg, ft_strlen(msg));
		return (1);
	}
	return (0);
}

void	display_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("[%d]: %s\n", i, tokens[i]);
		i++;
	}
}
