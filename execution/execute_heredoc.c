/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:18:59 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/12 21:39:28 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_delimiter(char *line, char *delim, int dlen)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (ft_strncmp(line, delim, dlen) == 0 && ft_strlen(line) == dlen);
}

static int	read_heredoc_input(int pipe_fd, t_ast_node *node, char **envp)
{
	char	*line;
	char	*all;
	char	*new;
	char	*tmp;

	all = ft_strdup("");
	while (all && (write(STDOUT_FILENO, "> ", 2), 1))
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || (check_delimiter(line, node->filename,
					ft_strlen(node->filename)) && (free(line), 1)))
			break ;
		tmp = line;
		if (node->heredoc_expand)
			tmp = expand_variables(line, envp);
		new = malloc(ft_strlen(all) + ft_strlen(tmp) + 2);
		if (new)
			(strcpy(new, all), strcat(new, tmp), strcat(new, "\n"));
		if (node->heredoc_expand)
			free(tmp);
		(free(all), free(line), all = new);
	}
	if (all && ft_strlen(all) > 0)
		write(pipe_fd, all, ft_strlen(all));
	return (free(all), 0);
}

static int	execute_heredoc_parent(int *pipe_fd, int saved_stdin,
	t_ast_node *node, char ***envp)
{
	int	exit_status;
	int	status;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	exit_status = execute_ast(node->right, envp);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	wait(&status);
	setup_signals();
	if (WIFSIGNALED(status))
		return (130);
	return (exit_status);
}

static void	skip_chained_heredocs(t_ast_node *node)
{
	char	*line;
	int		dlen;

	if (!node->left || (node->left->type != AST_REDIR_HEREDOC
			&& node->left->type != AST_REDIR_IN))
		return ;
	if (node->left->left)
		skip_chained_heredocs(node->left);
	dlen = ft_strlen(node->left->filename);
	while (1 && (write(STDOUT_FILENO, "> ", 2), 1))
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || (check_delimiter(line, node->left->filename, dlen)
				&& (free(line), 1)))
			break ;
		free(line);
	}
}

int	execute_heredoc(t_ast_node *node, char ***envp)
{
	int		pipe_fd[2];
	int		saved_stdin;
	pid_t	pid;

	skip_chained_heredocs(node);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	saved_stdin = dup(STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(pipe_fd[0]), close(pipe_fd[1]), 1);
	if (pid == 0)
	{
		setup_heredoc_signals();
		close(pipe_fd[0]);
		read_heredoc_input(pipe_fd[1], node, *envp);
		close(pipe_fd[1]);
		exit(0);
	}
	setup_parent_signals();
	return (execute_heredoc_parent(pipe_fd, saved_stdin, node, envp));
}
