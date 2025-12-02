/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:45:00 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/20 13:13:30 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_type	get_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (AST_REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (AST_REDIR_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (AST_REDIR_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (AST_REDIR_HEREDOC);
	return (AST_COMMAND);
}

int	is_redirection(char *token)
{
	if (!token)
		return (0);
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0);
}
