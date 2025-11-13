# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 16:44:09 by aareslan          #+#    #+#              #
#    Updated: 2025/11/11 21:22:47 by aareslan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I.
LDFLAGS = -lreadline

SRC = minishell.c \
	signals/signals.c \
	signals/signals1.c \
	signals/exit_status.c \
	utils/utils_helpme_1.c \
	utils/utils_helpme_2.c \
	utils/utils_helpme_3.c \
	utils/utils_helpme_4.c \
	utils/utils_helpme_5.c \
	utils/utils_helpme_6.c \
	utils/utils_helpme_7.c \
	tokenization/cleanup_tokens_utils.c \
	tokenization/count_tokens.c \
	tokenization/extract_operator.c \
	tokenization/extract_quotes.c \
	tokenization/extract_word_utils.c \
	tokenization/fill_tokens.c \
	tokenization/free_tokens.c \
	tokenization/syntax_checker.c \
	tokenization/tokenizer.c \
	parsing/parser.c \
	parsing/parser_utils.c \
	parsing/parse_command.c \
	parsing/parse_redirection.c \
	parsing/parse_pipeline.c \
	expansion/append_utils.c \
	expansion/expand_exit_code.c\
	expansion/expand_tokens.c\
	expansion/expand_variables.c \
	expansion/get_var_name.c \
	expansion/getenv_value.c \
	expansion/handle_dollar.c \
	execution/execute_heredoc.c \
	execution/executor.c \
	execution/redirections.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	builtins/envp.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_exit.c \
	builtins/ft_unset.c \
	execution/is_builtin.c \
	execution/execute_builtin.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
