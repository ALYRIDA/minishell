/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_consume.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:30:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/26 23:49:24 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_eof_warning(char *delimiter)
{
	write(STDERR_FILENO, "\nbash: warning: here-document at line 1 ", 40);
	write(STDERR_FILENO, "delimited by end-of-file (wanted `", 34);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", 3);
}

void	print_bash_eof_warning(char *delimiter)
{
	write(STDERR_FILENO, "\nbash: warning: here-document at line 1 ", 40);
	write(STDERR_FILENO, "delimited by end-of-file (wanted `", 34);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", 3);
}

void	consume_single_heredoc(char *delimiter)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_delimiter_match(line, delimiter))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	consume_heredocs_in_left_chain(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		consume_heredocs_in_left_chain(node->left);
	if (node->type == AST_REDIR_HEREDOC)
		consume_single_heredoc(node->filename);
}

void	consume_all_chained_heredocs(t_ast_node *node)
{
	if (!node)
		return ;
	consume_heredocs_in_left_chain(node);
}
