/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:29 by aareslan          #+#    #+#             */
/*   Updated: 2025/12/02 21:43:42 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <ctype.h>
# include <string.h>
# include <stddef.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include <sys/wait.h>

typedef struct s_expand_ctx
{
	char	**res;
	int		*len;
	char	**envp;
}	t_expand_ctx;

typedef struct s_word_ctx
{
	char	**current;
	int		*len;
	int		*had_content;
}	t_word_ctx;

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_REDIR_APPEND,
	AST_REDIR_HEREDOC
}	t_ast_type;

typedef struct s_ast_node
{
	t_ast_type			type;
	char				**args;
	char				*filename;
	int					heredoc_expand;
	int					heredoc_fd;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

static volatile sig_atomic_t	g_signal;

/* signals */
void		setup_signals(void);
void		setup_heredoc_signals(void);
void		setup_heredoc_parent_signals(void);
void		setup_child_signals(void);
void		setup_parent_signals(void);
void		handle_sigint_heredoc(int sig);
void		handle_sigint_heredoc_parent(int sig);
int			get_signal(void);
void		reset_signal(void);
void		set_exit_status(int status);
int			get_exit_status(void);

/* utils */
int			ft_strlen(const char *str);
char		*ft_strdup(char *str);
int			is_whitespace(char c);
int			is_special_char(char c);
int			ft_strcmp(char *s1, char *s2);
int			ft_getpid(void);

/* tokenization */
void		free_tokens(char **tokens);

/* tokenizer helpers */
int			skip_operator(const char *s, int *i);
int			skip_quotes(const char *s, int *i);
int			skip_word(const char *s, int *i);

int			handle_operator(const char *s, int *i);
int			handle_quotes(const char *s, int *i);
int			handle_word(const char *s, int *i);
int			count_tokens(const char *s);

char		*extract_double_quotes(const char *s, int *i, char **envp,
				int in_single);
char		*extract_single_quotes(const char *s, int *i);
int			check_unclosed_quotes(const char *s);
char		*extract_word(const char *s, int *i, char **envp);
char		*extract_operator(const char *s, int *i);
void		fill_tokens(const char *s, char **tokens, char **envp);
char		*ft_substr_dup(const char *s, int start, int end);
char		**tokenize(const char *s, char **envp);
int			check_syntax(char **tokens);

char		*strip_quote_marker(char *str);
void		strip_markers_from_args(char **args);

/* input validation */
int			check_quotes(char *input);

/* extract_word helpers */
int			is_empty_quote_marker(char *part, int had_content, const char *s,
				int i);
int			handle_double_quote(const char *s, int *i, char **envp,
				t_word_ctx *ctx);
int			handle_single_quote(const char *s, int *i, t_word_ctx *ctx);
char		*extract_unquoted_part(const char *s, int *i, char **envp);
int			should_keep_token(const char *token);
int			count_valid_tokens(char **tokens);
void		copy_valid_tokens(char **tokens, char **clean);

/* string/char utils */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

/* expansion */
void		append_char(char **res, char c, int *len);
void		append_str(char **res, char *str, int *len);
char		*get_var_name(char *s, int *i);
void		expand_exit_code(char **res, int *len, int *i);
char		*getenv_value(char **envp, char *name);
void		handle_dollar(char *input, int *i, t_expand_ctx *ctx);
char		*expand_variables(char *input, char **envp);

int			is_explicit_empty(const char *s);
int			ft_tablen(char **tab);;
char		**expand_tokens(char **tokens, char **envp);
int			count_total_tokens(char **tokens);
void		add_split_tokens(char **result, int *k, char *token);
int			count_words_in_token(char *token);
int			should_split_token(char *token);
int			has_quote_marker(char *token);
char		**split_token_by_spaces(char *token);

char		**cleanup_tokens(char **tokens);

/* parsing */
t_ast_node	*parse_tokens(char **tokens);
t_ast_node	*create_ast_node(t_ast_type type);
void		free_ast(t_ast_node *node);
// void		print_ast(t_ast_node *node);
t_ast_type	get_redir_type(char *token);
int			is_redirection(char *token);
t_ast_node	*parse_simple_command(char **tokens, int *i);
t_ast_node	*parse_command_redirections(char **tokens, int *i);
t_ast_node	*parse_redirection(char **tokens, int *i);
t_ast_node	*parse_cmd_with_redirections(char **tokens, int *i);
t_ast_node	*parse_pipeline(char **tokens);
int			count_args_with_redirections(char **tokens, int start);
int			count_args(char **tokens, int start);
void		fill_args_with_redirections(char **tokens, int *i, char **args);
void		fill_args(char **tokens, int *i, char **args);
t_ast_node	*create_default_cmd(char **tokens, int i);

/* execution */
char		*resolve_command_path(char *cmd, char **envp);
char		*extract_dir(char *path_env, int start, int end);
int			execute_ast(t_ast_node *node, char ***envp);
int			execute_command(t_ast_node *node, char ***envp);
int			execute_pipeline(t_ast_node *node, char ***envp);
int			exec_pipeline_recursive(t_ast_node *node, char ***envp,
				int input_fd, int *last_pid);
int			process_pipeline_heredocs(t_ast_node *node, char ***envp);
int			collect_pipeline_heredocs(t_ast_node *node, char ***envp);
int			wait_last_child(int last_pid, int *last_status);
void		strip_markers_from_args(char **args);
int			execute_redirect_stdin(t_ast_node *node, char ***envp);
int			validate_redirections_stdin(t_ast_node *node);
int			execute_redirect_out(t_ast_node *node, char ***envp);
int			execute_redirect_append(t_ast_node *node, char ***envp);
int			validate_all_redirections(t_ast_node *node);
int			validate_all_redirections_before_open(t_ast_node *node);
int			open_intermediate_files(t_ast_node *node);
int			process_redirections_left_to_right(t_ast_node *node,
				int *saved_stdin, int *saved_stdout);
int			restore_execute_stdin(int fd, int saved_stdin,
				t_ast_node *node, char ***envp);
t_ast_node	*find_command_node(t_ast_node *node);
char		*find_last_slash(const char *str);
void		write_permission_error(const char *filename);
int			process_out_redir(t_ast_node *node, int *saved_stdout);
int			process_append_redir(t_ast_node *node, int *saved_stdout);
int			process_in_redir(t_ast_node *node, int *saved_stdin);
int			process_heredoc_redir(t_ast_node *node, int *saved_stdin);
int			process_all_heredocs_first(t_ast_node *node, char ***envp);
int			execute_heredoc(t_ast_node *node, char ***envp);
void		consume_all_chained_heredocs(t_ast_node *node);
void		read_heredoc_content(int write_fd, char *delimiter, int expand,
				char **envp);
int			wait_for_heredoc_child(pid_t pid);
void		print_eof_warning(char *delimiter);
int			is_delimiter_match(char *line, char *delimiter);
char		*append_line_to_content(char *content, char *line, int expand,
				char **envp);
char		*read_next_heredoc_line(char *delimiter);
char		*process_heredoc_line(char *content, char *delimiter, int expand,
				char **envp);
char		*read_all_heredoc_lines(char *delimiter, int expand, char **envp,
				int *found_delimiter);
int			is_builtin(char *cmd);
int			execute_builtin(char **args, char ***envp);

/*builtins*/
int			ft_cd(char **argv, char ***envp);
int			is_n_flag(char *arg);
int			ft_env(char **envp);
int			ft_export(char **argv, char ***envp);
void		print_sorted_entry(char *entry);
void		sort_env_array(char **sorted, int len);
int			ft_pwd(void);
int			ft_echo(char **argv);
int			ft_exit(char **args);
int			ft_unset(char **args, char ***envp);

/* environment management */
char		**copy_environment(char **envp);
char		**copy_environment_with_incremented_shlvl(char **envp);
void		free_environment(char **envp);
void		increment_shlvl(char **envp);
int			increment_shlvl_in_env(char **envp);
int			ft_atoi_shlvl(const char *str);

/* main helpers */
int			handle_exit(char *input);
int			handle_syntax_error(char **tokens);
void		process_tokens(char **tokens, char ***envp);

#endif
