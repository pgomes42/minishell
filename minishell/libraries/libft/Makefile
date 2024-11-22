# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomes <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 06:55:33 by pgomes            #+#    #+#              #
#    Updated: 2024/11/22 13:30:33 by pgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CLR_RMV		:= \033[0m
RED		:= \033[1;31m
GREEN		:= \033[1;32m
CYAN 		:= \033[1;36m


NAME        	= libft.a
CC        	= cc
FLAGS    	= -Wall -Wextra -Werror -g
LIBC 		= ar rcs
RM		= rm -f
OBJ_DIR		= mkdir
SRCS        	=      get_next_line/get_next_line.c \
                          get_next_line/get_next_line_utils.c \
                          printf/ft_printf.c \
                          printf/puthex.c \
                          printf/ft_putpointer.c \
                          libft/ft_strlcat.c \
                          libft/ft_strchr.c \
                          libft/ft_tolower.c \
                          libft/ft_memset.c \
                          libft/ft_strrchr.c \
                          libft/ft_lstnew_bonus.c \
                          libft/ft_lstadd_back_bonus.c \
                          libft/ft_calloc.c \
                          libft/ft_strmapi.c \
                          libft/ft_bzero.c \
                          libft/ft_lstlast_bonus.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strnstr.c \
                          libft/ft_lstclear_bonus.c \
                          libft/ft_isdigit.c \
                          libft/ft_memcpy.c \
                          libft/ft_isalnum.c \
                          libft/ft_memmove.c \
                          libft/ft_stristri.c \
                          libft/ft_strncmp.c \
                          libft/ft_strcmp.c \
                          libft/ft_itoa.c \
                          libft/ft_atoi.c \
                          libft/ft_substr.c \
                          libft/ft_split.c \
                          libft/ft_utoa.c \
                          libft/ft_memcmp.c \
                          libft/ft_isascii.c \
                          libft/ft_isprint.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_lstsize_bonus.c \
                          libft/ft_isalpha.c \
                          libft/ft_lstadd_front_bonus.c \
                          libft/ft_toupper.c \
                          libft/ft_lstdelone_bonus.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_strdup.c \
                          libft/ft_strlen.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_lstmap_bonus.c \
                          libft/ft_strtrim.c \
                          libft/ft_memchr.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_lstiter_bonus.c \
                          libft/ft_strjoin.c \
                          libft/ft_strjoin_f.c \
                          
OBJS        = $(SRCS:.c=.o)

.c.o: 
	@ ${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	 ${OBJS} 
			@ ${LIBC} ${NAME} ${OBJS}
			@ echo "$(GREEN)$(NAME) created[0m ✔️"

all:		@ ${NAME}

bonus:		all

clean:
			@ ${RM} ${OBJS}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


