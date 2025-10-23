# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aareslan <aareslan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 16:44:09 by aareslan          #+#    #+#              #
#    Updated: 2025/10/22 15:02:31 by aareslan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I.
LDFLAGS = -lreadline

SRC = minishell.c \
	signals/signals.c \
	utils/utils_helpme_1.c \
	utils/utils_helpme_2.c \
	utils/utils_helpme_3.c \
	utils/utils_helpme_4.c \
	utils/utils_helpme_5.c \
	utils/utils_helpme_6.c \
	tokenization/count_tokens.c \
	tokenization/create_parse_ast.c \
	tokenization/extract_operator.c \
	tokenization/extract_quotes.c \
	tokenization/fill_tokens.c \
	tokenization/free_tokens.c \
	tokenization/free_ast.c \
	tokenization/parse_command_ast.c \
	tokenization/tokenizer.c \
	expansion/append_utils.c \
	expansion/expand_exit_code.c\
	expansion/expand_tokens.c\
	expansion/expand_variables.c \
	expansion/get_var_name.c \
	expansion/getenv_value.c \
	expansion/handle_dollar.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
