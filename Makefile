# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lseiberr <marvin@42perpignan.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 21:58:09 by gdornic           #+#    #+#              #
#    Updated: 2023/12/17 08:47:56 by lseiberr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

DEP = libft

HEADERS = -Ilibft

LIB_LINK = -L/usr/include -lreadline -Llibft -lft

BUILTIN_SRC = builtin/reverse_split.c builtin/sort_env.c builtin/utils.c builtin/pwd_builtin.c builtin/echo_builtin.c builtin/cd_builtin.c builtin/env_builtin.c builtin/exit_builtin.c builtin/utils_export.c builtin/export_builtin.c builtin/unset_builtin.c builtin/signals.c

SRC = $(BUILTIN_SRC) main.c array_free.c tokenizer.c definitions.c definitions2.c definitions3.c definitions4.c token_print.c function_variables.c parser.c syntax_rules.c execution.c pipeline_execution.c command_execution.c redirection.c builtin_execution.c program_execution.c expansion.c delete_node.c parameter_expansion.c str_merge.c stream.c word_split.c filename_expansion.c wildcard_expansion.c lstnew_secure.c quote_removal.c path_split.c next_list_operator.c quote_rule.c next_mark.c next_pipe.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

define make_dep
	for d in $(DEP) ; do \
		make -C $$d $(1) ; \
	done
endef

all: $(NAME)

$(NAME): $(OBJ)
	$(call make_dep,all)
	$(CC) $(OBJ) $(HEADERS) $(LIB_LINK) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(call make_dep,clean)

fclean: clean
	rm -f $(NAME)
	$(call make_dep,fclean)

re: fclean all
