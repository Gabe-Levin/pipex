# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glevin <glevin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:11:59 by glevin            #+#    #+#              #
#    Updated: 2024/11/12 11:34:18 by glevin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror -g
ARFLAGS = rcs

# Directories
SRC_DIR = ./src
MASTERLIB_DIR = ./masterLib

# Library name
NAME = pipex

# Source Files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/here_doc.c 

# Object Files
OBJS = $(SRCS:.c=.o)

# MasterLib
MASTERLIB = $(MASTERLIB_DIR)/masterLib.a

# Default Target: Build the library
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJS) $(MASTERLIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MASTERLIB) 

# Rule to ensure masterLib is compiled
$(MASTERLIB):
	@make -C $(MASTERLIB_DIR)

# Rule to compile .c files to .o files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ && echo "\033[32m✔\033[0m $< compiled successfully"

# Clean up object files
clean:
	rm -f $(OBJS)
	@make -C $(MASTERLIB_DIR) clean
	echo "\033[31m🗑️\033[0m  Object files removed"

# Clean up objects files and the library
fclean: clean
	rm -f $(NAME)
	@make -C $(MASTERLIB_DIR) fclean
	echo "\033[31m🗑️\033[0m  Library removed"

# Rebuild the library
re: fclean all

.PHONY: all clean fclean re
