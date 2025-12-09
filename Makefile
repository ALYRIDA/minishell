# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 16:44:09 by aareslan          #+#    #+#              #
#    Updated: 2025/12/09 16:40:02 by aareslan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I.
LDFLAGS = -lreadline

# Colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
CYAN = \033[1;36m
RED = \033[1;31m
RESET = \033[0m

SRC = minishell.c \
	minishell_utils.c \
	signal_handler/signals.c \
	signal_handler/signals1.c \
	signal_handler/exit_status.c \
	utils/banner.c \
	utils/string_utils.c \
	utils/token_skip_utils.c \
	utils/char_compare_utils.c \
	utils/char_check_utils.c \
	utils/char_conversion_utils.c \
	utils/misc_utils.c \
	utils/shlvl_increment.c \
	utils/quote_marker_utils.c \
	utils/env_copy_utils.c \
	utils/env_free_utils.c \
	tokenizer/cleanup_tokens_utils.c \
	tokenizer/count_tokens.c \
	tokenizer/extract_operator.c \
	tokenizer/extract_quotes.c \
	tokenizer/extract_word_utils.c \
	tokenizer/fill_tokens.c \
	tokenizer/free_tokens.c \
	tokenizer/syntax_checker.c \
	tokenizer/tokenizer.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/parse_command.c \
	parser/parse_command_utils.c \
	parser/parse_command_utils2.c \
	parser/parse_redirection.c \
	parser/parse_pipeline.c \
	expander/append_utils.c \
	expander/expand_exit_code.c\
	expander/expand_tokens.c\
	expander/expand_tokens_utils.c\
	expander/expand_variables.c \
	expander/get_var_name.c \
	expander/getenv_value.c \
	expander/handle_dollar.c \
	executor/heredoc_executor.c \
	executor/heredoc_utils.c \
	executor/heredoc_fd_utils.c \
	executor/heredoc_reader.c \
	executor/heredoc_consumer.c \
	executor/heredoc_consumer_utils.c \
	executor/cmd_path_resolver.c \
	executor/cmd_path_utils.c \
	executor/ast_executor.c \
	executor/cmd_executor.c \
	executor/pipeline_executor.c \
	executor/heredoc_processor.c \
	executor/heredoc_collector.c \
	executor/pipeline_wait.c \
	executor/redir_processor.c \
	executor/redir_utils.c \
	executor/redir_heredoc_utils.c \
	executor/redir_executor.c \
	executor/redir_validator.c \
	executor/redir_validator_stdin.c \
	executor/redir_permissions.c \
	executor/redir_heredoc_handler.c \
	executor/redir_fd_restore.c \
	executor/redir_error_handler.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	builtin_commands/envp.c \
	builtin_commands/ft_cd.c \
	builtin_commands/ft_cd_utils.c \
	builtin_commands/ft_echo.c \
	builtin_commands/ft_env.c \
	builtin_commands/ft_export.c \
	builtin_commands/ft_export_utils.c \
	builtin_commands/ft_pwd.c \
	builtin_commands/ft_exit.c \
	builtin_commands/ft_unset.c \
	executor/builtin_checker.c \
	executor/builtin_executor.c 

OBJ = $(SRC:.c=.o)
TOTAL_FILES = $(words $(SRC))
CURRENT = 0

all: banner $(NAME)

banner:
	@echo "$(CYAN)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ██║╚══════╝╚══════╝╚══════╝"
	@echo "$(RESET)"
	@echo "$(YELLOW)        🐚  Compiling Sirine and Aly Rida Minishell  🐚$(RESET)"
	@echo ""

%.o: %.c
	@$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	@printf "$(GREEN)[%3d/%3d]$(RESET) Compiling $(BLUE)%-40s$(RESET)\n" $(CURRENT) $(TOTAL_FILES) $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo ""
	@echo "$(YELLOW)🔗 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"
	@echo ""

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re banner
