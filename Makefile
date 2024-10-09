# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 16:06:48 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/10/09 16:27:07 by kkhai-ki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

INCLUDE = -Iinclude

SRC_DIR = src

SRC_FILES =	main

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

all :
		@mkdir -p $(OBJ_DIR)
		@make $(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) :	$(OBJ)
			@printf "$(GREEN)philo object files created.$(RESET)\n"
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBRARIES) && echo "$(GREEN)philo created.$(RESET)"

clean :
			@rm -rf $(OBJ_DIR) && echo "$(RED)philo object files deleted.$(RESET)"

fclean:
			@rm -rf $(OBJ_DIR) $(NAME) && echo "$(RED)philo deleted.$(RESET)"
			@rm -rf $(OBJ_DIR) && echo "$(RED)philo object files deleted.$(RESET)"

re:			fclean all

.PHONY:	clean fclean re all
