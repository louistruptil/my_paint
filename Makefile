##
## EPITECH PROJECT, 2024
## MyPaint
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Iinclude
EXECNAME = my_paint
LIBMY = libmy.a
LIBMY_DIR = lib/my

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m
SRCS = ./src/main.c \
       ./src/gui/button.c \
       ./src/gui/dropdown.c \
       ./src/event.c \
       ./src/window.c \
       ./src/my_paint.c \
	   ./src/draw.c \
	   ./src/main_loop.c	\
	   ./src/gui/interface.c	\
	   ./src/action.c	\

OBJS = $(SRCS:./src/%.c=./obj/%.o)
OBJDIR = obj

LIB_SFML = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all: $(LIBMY) $(EXECNAME)

$(LIBMY):
	@echo -e "$(GREEN)Building libmy...$(NO_COLOR)"
	@$(MAKE) -C $(LIBMY_DIR)

$(EXECNAME): $(OBJS)
	@echo -e "$(GREEN)Linking $(EXECNAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $^ -L$(LIBMY_DIR) -lmy $(LIB_SFML) -o $@

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)Compiling $<...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning up...$(NO_COLOR)"
	@echo "Removing object files..."
	@rm -f $(OBJS)
	@echo "Removing directory: $(OBJDIR)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBMY_DIR) clean

fclean: clean
	@echo -e "$(RED)Removing executable $(EXECNAME)...$(NO_COLOR)"
	@rm -f $(EXECNAME)
	@$(MAKE) -C $(LIBMY_DIR) fclean

re: fclean all
	@echo -e "$(GREEN)Rebuilding...$(NO_COLOR)"

.PHONY: all clean fclean re
