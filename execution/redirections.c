/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 20:39:24 by aareslan          #+#    #+#             */
/*   Updated: 2025/10/29 15:41:05 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Execute input redirection: cmd < file
int	execute_redirect_in(t_ast_node *node, char ***envp)
{
	int	fd;			// File descriptor for the input file
	int	saved_stdin;// Save orginal stdin to restore later
	int	exit_status;// Store the exit status of the command

	// Open the file for reading
	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		// If file doesn't exist or can't be opened, print error
		perror(node->filename);
		return (1);
	}
	// Save the current stdin so we can restore it later
	saved_stdin = dup(STDIN_FILENO);
	// Redirect stdin to read from our file
	dup2(saved_stdin, STDIN_FILENO);
	close(fd); // Close orginal file descriptor (we have dup2'd it)
	// Execute the command (it will now read from our file instead of stdin)
	exit_status = execute_ast(node->right, envp);
	// Restore orginal stdin
	dup2(saved_stdin, STDIN_FILENO);
	close (saved_stdin);
	return (exit_status);
}

// Execute output redirection: cmd > file
int	execute_redirect_out(t_ast_node *node, char ***envp)
{
	int	fd;				// File descriptor for the output file
	int	saved_stdout;	// Save original stdout to restore later
	int	exit_status;	// Store the exit status of the command

	// open/create file for writing (truncate if exists)
	fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // 0644 ->>> this is file permission mode used when creating a new file (because of the O_CREAT flag in open() ).
	if (fd == -1)
	{
		perror (node->filename);
		return (1);
	}
	// Save current stdout
	saved_stdout = dup(STDOUT_FILENO);
	// Redirect stdout to write to our file
	dup2(fd, STDOUT_FILENO);
	close(fd);
	// Execute the command (it will now write to our file instead of stdout)
	exit_status = execute_ast(node->left, envp);
	// Restore orginal stdout
	dup2(saved_stdout ,STDOUT_FILENO);
	close(saved_stdout);
	return (exit_status);
}

// Execute append redirection: cmd >> file
int	execute_redirection_append(t_ast_node *node, char ***envp)
{
	int	fd;
	int	saved_stdout;
	int	exit_status;

	// Open/create file for writing (append mode - don't truncate)
	fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(node->filename);
		return (1);
	}
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exit_status = execute_ast(node->left, envp);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (exit_status);
}

// Execute here document: cmd << delimiter
int	execute_heredoc(t_ast_node *node, char ***envp)
{
	int		pipe_fd[2]; // Pipe to pass heredoc content to command
	int		saved_stdin;
	int		exit_status;
	pid_t	pid;
	char	*line;

	// Create a pipe for heredoc content
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	saved_stdin = dup(STDIN_FILENO);
	// Fork to handle heredoc input
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0) // Child process: read heredoc and write to pipe
	{
		close(pipe_fd[0]); // Close read end in child
		// Read lines until we see the delimiter
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2); // Heredoc prompt
			line = get_next_line(STDIN_FILENO); // You'll need to implement this
			if (!line || ft_strcmp(line, node->filename) == 0)
			{
				free (line);
				break ;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	else // Parent process: execute command with heredoc as input
	{
		close(pipe_fd[1]); // Close write end in parent
		// Redirect stdin to read from pipe
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		// Execute the command
		exit_status = execute_ast(node->right, envp);
		// Restore stdin and wait for child
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		waitpid(pid, NULL, 0);
	}
	return (exit_status);
}
