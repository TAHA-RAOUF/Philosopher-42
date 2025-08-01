# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moraouf <moraouf@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/15 00:00:00 by moraouf           #+#    #+#              #
#    Updated: 2025/08/01 22:26:25 by moraouf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
DEBUG_FLAGS = -g -pthread
INCLUDE = -I.

# Source files
SRCS = main.c init.c parssing.c helper.c philo.c monitor.c logique.c

# Object files
OBJS = $(SRCS:.c=.o)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"

%.o: %.c philo.h
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Debug version with thread sanitizer
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -f $(OBJS)
	@echo "$(GREEN)✓ Object files cleaned!$(NC)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(NC)"

# Rebuild everything
re: fclean all

# Test with different arguments
test: $(NAME)
	@echo "$(YELLOW)Testing with valid arguments...$(NC)"
	@echo "Test 1: 4 philosophers, 410ms die, 200ms eat, 200ms sleep"
	@./$(NAME) 4 410 200 200
	@echo "\nTest 2: 5 philosophers with meal count"
	@./$(NAME) 5 800 200 200 7
	@echo "\nTest 3: Invalid arguments (should fail)"
	@./$(NAME) 4 410 200
	@echo "\nTest 4: Too many philosophers (should fail)"
	@./$(NAME) 250 410 200 200

# Check for memory leaks (requires valgrind)
valgrind: $(NAME)
	@echo "$(YELLOW)Running valgrind...$(NC)"
	valgrind --tool=helgrind --history-level=approx ./$(NAME) 3 610 200 200 5

# Help
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  all      - Build the project"
	@echo "  debug    - Build with debug flags and thread sanitizer"
	@echo "  clean    - Remove object files"
	@echo "  fclean   - Remove object files and executable"
	@echo "  re       - Rebuild everything"
	@echo "  test     - Run basic tests"
	@echo "  valgrind - Run with valgrind (requires valgrind installed)"
	@echo "  help     - Show this help message"

.PHONY: all clean fclean re debug test valgrind help
