##
## EPITECH PROJECT, 2024
## LibMy
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Iinclude

LIBNAME = my
LIBRARY = lib$(LIBNAME).a
SRCS =   src/character/my_isdigit.c \
	 src/character/my_islower.c \
	 src/character/my_isspace.c \
	 src/character/my_isupper.c \
	 src/character/my_isalpha.c \
	 src/math/my_abs.c \
	 src/math/my_compute_power_rec.c \
	 src/math/my_compute_square_root.c \
	 src/memory/my_calloc.c \
	 src/memory/my_memcpy.c \
	 src/memory/my_memset.c \
	 src/memory/my_realloc.c \
	 src/memory/my_free_array.c \
	 src/standard/my_putchar.c \
	 src/standard/my_putnbr.c \
	 src/standard/my_putstr.c \
	 src/string/my_atoi.c \
	 src/string/my_itoa.c \
	 src/string/my_revstr.c \
	 src/string/my_str_isalpha.c \
	 src/string/my_str_islower.c \
	 src/string/my_str_isnum.c \
	 src/string/my_str_isprintable.c \
	 src/string/my_str_isupper.c \
	 src/string/my_str_to_word_array.c \
	 src/string/my_strcat.c \
	 src/string/my_strchr.c \
	 src/string/my_strcmp.c \
	 src/string/my_strcpy.c \
	 src/string/my_strdup.c \
	 src/string/my_strlen.c \
	 src/string/my_strlowcase.c \
	 src/string/my_strncat.c \
	 src/string/my_strncmp.c \
	 src/string/my_strncpy.c \
	 src/string/my_strrchr.c \
	 src/string/my_strstr.c \
	 src/string/my_strupcase.c \
	 src/misc/my_array_len.c
OBJS = $(SRCS:src/%.c=obj/%.o)

OBJDIR = obj

GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	@echo -e "$(YELLOW)Building $@...$(NC)"
	@ar rcs $@ $^

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
