/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:04:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/27 20:04:00 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_heredoc_line(char *content, char *delimiter, int expand,
		char **envp)
{
	char	*line;

	line = read_next_heredoc_line(delimiter);
	if (!line || line == (char *)-1)
		return (line);
	content = append_line_to_content(content, line, expand, envp);
	free(line);
	return (content);
}

char	*read_all_heredoc_lines(char *delimiter, int expand, char **envp,
		int *found_delimiter)
{
	char	*content;
	char	*result;

	content = ft_strdup("");
	if (!content)
		exit(1);
	*found_delimiter = 0;
	while (1)
	{
		result = process_heredoc_line(content, delimiter, expand, envp);
		if (!result)
			break ;
		if (result == (char *)-1)
		{
			*found_delimiter = 1;
			break ;
		}
		content = result;
		if (!content)
			exit(1);
	}
	return (content);
}

void	read_heredoc_content(int write_fd, char *delimiter, int expand,
		char **envp)
{
	char	*content;
	int		found_delimiter;

	content = read_all_heredoc_lines(delimiter, expand, envp,
			&found_delimiter);
	if (!found_delimiter)
		print_eof_warning(delimiter);
	if (content && ft_strlen(content) > 0)
		write(write_fd, content, ft_strlen(content));
	free(content);
}
