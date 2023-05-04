# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 09:37:39 by jalevesq          #+#    #+#              #
#    Updated: 2023/05/04 14:57:19 by jalevesq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 -fsanitize=address
RM = rm -rf

INC_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = philo.c init.c thread_func.c thread_even.c thread_odd.c \
	ft_atoi.c isdead.c utils.c ft_isdigit.c parsing.c

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})

GREEN	= \033[32;1m
CYAN	= \033[36;1m
RED		= \033[0;31m
BOLD	= \033[1m
RESET	= \033[0m
MAGENTA	=\033[0;95m

all: ${NAME}



${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@${CC} ${CFLAGS} -I ${INC_DIR} -c $< -o $@
	@echo "$(GREEN)Compiling: $<$(RESET)$(MAGENTA)              [OK]$(RESET)"

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)Compilation successfully completed."

clean:
	@${RM} ${OBJS_DIR}
	@echo "$(RED)$(BOLD)Cleaning successfully completed."

fclean:	clean
	@${RM} ${NAME}

re: fclean all
	@echo "$(CYAN)Recompilation completed"

.PHONY: all clean fclean re
