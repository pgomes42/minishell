# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 10:36:38 by pgomes            #+#    #+#              #
#    Updated: 2024/11/21 07:08:48 by pgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
CYAN 		:= \033[1;36m

NAME		:= minishell
OBJ_DIR		:= obj
LIBFT		:= libft.a
LIBFT_PATH	:= "libraries/libft"

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g

READLINE_PATH:= /goinfre/homebrew/opt/readline

SRCS		:=	src/builtins/cd.c \
				src/builtins/echo.c \
				src/builtins/env_utils.c \
				src/builtins/env.c \
				src/builtins/exit.c \
				src/builtins/export.c \
				src/builtins/pwd.c \
				src/builtins/unset.c \
				src/expander/ft_asterisker.c \
				src/expander/ft_expand_utils.c \
				src/expander/ft_expand.c \
				src/expander/ft_expander_split.c \
				src/expander/ft_globber_utils.c \
				src/expander/ft_globber.c \
				src/expander/ft_strip_quotes.c \
				src/expander/heredoc_expander.c \
				src/tokenizing/tokenizer_appenders.c \
				src/tokenizing/tokenizer_handlers.c \
				src/tokenizing/tokenizer_lst.c \
				src/tokenizing/tokenizer_utils.c \
				src/prompt/prompt.c \
				src/garbage_collector/exec_utils.c \
				src/garbage_collector/free_str.c \
				src/exe/ft_exec_simple_cmd.c \
				src/heroduc/heroduc.c \
				src/exe/exec.c \
				src/exe/exec_builtin.c \
				src/exe/exec_redirect.c \
				src/exe/ft_get_path.c \
				src/exe/exist_check.c \
				src/main.c \
				src/main_signals.c \
				src/utils/utils.c

OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:src/%.c=%.o))

# Criação dos arquivos .o na pasta obj
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline -g
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
