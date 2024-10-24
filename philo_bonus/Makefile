# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 16:06:48 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/10/24 15:34:42 by kkhai-ki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g3 #-fsanitize=address

INCLUDE = -Iinclude

SRC_DIR = src

SRC_FILES =	main	\
			parse	\
			init	\
			utils	\
			philosophers	\
			ipc	\
			monitor

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all :
		@mkdir -p $(OBJ_DIR)
		@make $(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) :	$(OBJ)
			@printf "$(GREEN)philo_bonus object files created.$(RESET)\n"
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) && echo "$(GREEN)philo_bonus created.$(RESET)"

clean :
			@rm -rf $(OBJ_DIR) && echo "$(RED)philo_bonus object files deleted.$(RESET)"

fclean:
			@rm -rf $(OBJ_DIR) $(NAME) && echo "$(RED)philo_bonus deleted.$(RESET)"
			@rm -rf $(OBJ_DIR) && echo "$(RED)philo_bonus object files deleted.$(RESET)"

re:			fclean all

.PHONY:	clean fclean re all
