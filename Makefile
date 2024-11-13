# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glevin <glevin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:11:59 by glevin            #+#    #+#              #
#    Updated: 2024/11/13 13:09:25 by glevin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror -g
ARFLAGS = rcs

# Directories
SRC_DIR = ./src
SRC_BONUS_DIR = ./src_bonus
MASTERLIB_DIR = ./masterLib

# Library name
NAME = pipex
BONUS_NAME = pipex_bonus

# Source Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c
SRCS_BONUS = $(SRC_BONUS_DIR)/main_bonus.c $(SRC_BONUS_DIR)/utils_bonus.c $(SRC_BONUS_DIR)/here_doc_bonus.c

# Object Files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# MasterLib
MASTERLIB = $(MASTERLIB_DIR)/masterLib.a

# Default Target: Build the library
all: $(NAME)

# Bonus Target: Build the bonus version
bonus: $(BONUS_NAME)

# Rule to create the main library
$(NAME): $(OBJS) $(MASTERLIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MASTERLIB)

# Rule to create the bonus library
$(BONUS_NAME): $(OBJS_BONUS) $(MASTERLIB)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS) $(MASTERLIB)

# Rule to ensure masterLib is compiled
$(MASTERLIB):
	@make -C $(MASTERLIB_DIR)

# Rule to compile .c files to .o files for src
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[32m✔\033[0m $< compiled successfully"

# Rule to compile .c files to .o files for src_bonus
$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[32m✔\033[0m $< compiled successfully"

# Clean up object files
clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	@make -C $(MASTERLIB_DIR) clean
	echo "\033[31m🗑️\033[0m  Object files removed"

# Clean up objects files and the libraries
fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@make -C $(MASTERLIB_DIR) fclean
	echo "\033[31m🗑️\033[0m  Libraries removed"

# Rebuild the library
re: fclean all

.PHONY: all bonus clean fclean re
