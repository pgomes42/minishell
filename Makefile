# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 10:36:38 by pgomes            #+#    #+#              #
#    Updated: 2025/09/16 12:22:54 by pgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
CYAN 		:= \033[1;36m

NAME		:= minishell
OBJ_DIR		:= obj
HEADER		:= include/minishell.h
LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g


SRCS		:=	src/tokenizing/tokenizing.c\
			src/tokenizing/token_list.c\
			src/tokenizing/token_utils.c\
			src/tokenizing/token_utils_two.c\
			src/env/env_list.c\
			src/ast/ast.c\
			src/builtins/cd.c\
			src/builtins/echo.c\
			src/builtins/unset.c\
			src/builtins/export.c\
			src/builtins/exit.c\
			src/builtins/pwd.c\
			src/execute/exec_builtins.c\
			src/execute/execute.c\
			src/execute/execute_utils.c\
			src/utils/load_argv.c\
			src/utils/clear.c\
			src/utils/signal.c\
			src/expander/expander.c\
			src/ast/ast_utils.c\
			src/main.c
				
				

OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:src/%.c=%.o))

$(OBJ_DIR)/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinclude

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft  -lreadline
	@echo "$(GREEN)$(NAME) created$(CLR_RMV) ✔️"

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Deleting $(CYAN)$(OBJ_DIR)$(CLR_RMV) objs ✔️"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "$(RED)Deleting $(CYAN)$(NAME)$(CLR_RMV) binary ✔️"

re: fclean all

.PHONY: all clean fclean re
