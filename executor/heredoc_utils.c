/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhalil <skhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:30:00 by skhalil           #+#    #+#             */
/*   Updated: 2025/11/26 23:15:32 by skhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter_match(char *line, char *delimiter)
{
	int	line_len;

	if (!line || !delimiter)
		return (0);
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	return (ft_strcmp(line, delimiter) == 0);
}

static char	*get_expanded_line(char *line, int expand, char **envp)
{
	if (expand)
		return (expand_variables(line, envp));
	return (ft_strdup(line));
}

char	*append_line_to_content(char *content, char *line, int expand,
		char **envp)
{
	char	*expanded_line;
	char	*new_content;
	int		content_len;
	int		line_len;

	if (!content)
		content = ft_strdup("");
	if (!content)
		return (NULL);
	expanded_line = get_expanded_line(line, expand, envp);
	if (!expanded_line)
		return (free(content), NULL);
	content_len = ft_strlen(content);
	line_len = ft_strlen(expanded_line);
	new_content = malloc(content_len + line_len + 2);
	if (!new_content)
		return (free(content), free(expanded_line), NULL);
	ft_memcpy(new_content, content, content_len);
	ft_memcpy(new_content + content_len, expanded_line, line_len);
	new_content[content_len + line_len] = '\n';
	new_content[content_len + line_len + 1] = '\0';
	return (free(content), free(expanded_line), new_content);
}

char	*read_next_heredoc_line(char *delimiter)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	if (is_delimiter_match(line, delimiter))
		return (free(line), (char *)-1);
	return (line);
}
