/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:44:29 by aareslan          #+#    #+#             */
/*   Updated: 2025/11/11 22:52:09 by aareslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
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
void		setup_child_signals(void);
void		setup_parent_signals(void);
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

char		**cleanup_tokens(char **tokens);

/* parsing */
t_ast_node	*parse_tokens(char **tokens);
t_ast_node	*create_ast_node(t_ast_type type);
void		free_ast(t_ast_node *node);
// void		print_ast(t_ast_node *node);
t_ast_type	get_redir_type(char *token);
int			is_redirection(char *token);
t_ast_node	*parse_simple_command(char **tokens, int *i);
t_ast_node	*parse_redirection(char **tokens, int *i);
t_ast_node	*parse_cmd_with_redirections(char **tokens, int *i);
t_ast_node	*parse_pipeline(char **tokens);

/* execution */
int			execute_ast(t_ast_node *node, char ***envp);
int			execute_command(t_ast_node *node, char ***envp);
int			execute_pipeline(t_ast_node *node, char ***envp);
int			execute_redirect_in(t_ast_node *node, char ***envp);
int			execute_redirect_out(t_ast_node *node, char ***envp);
int			execute_redirect_append(t_ast_node *node, char ***envp);
int			execute_heredoc(t_ast_node *node, char ***envp);
int			is_builtin(char *cmd);
int			execute_builtin(char **args, char ***envp);

/*builtins*/
int			ft_cd(char **argv, char ***envp);
int			is_n_flag(char *arg);
int			ft_env(char **envp);
int			ft_export(char **argv, char ***envp);
int			ft_pwd(void);
int			ft_echo(char **argv);
int			ft_exit(char **args);
int			ft_unset(char **args, char ***envp);

/* environment management */
char		**copy_environment(char **envp);
void		free_environment(char **envp);

#endif
