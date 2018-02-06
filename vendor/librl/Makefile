# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/11 12:29:40 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = librl.a
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fno-omit-frame-pointer -fsanitize=address

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include ../libft/include
3TH_PATH =

LIB_NAME =
3TH_NAME =
SRC_NAME = \
	edit.c edit/ctrl.c edit/hist.c edit/insert.c edit/move.c edit/print.c \
	edit/return.c edit/ln.c edit/utf8.c \
	hist.c hist/load.c hist/save.c \
	hook.c \
	read.c read/notty.c read/tty.c \
	screen.c \
	visual.c \
	signal.c

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
INC = $(addprefix -I, $(INC_PATH))
3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
LIB = $(addprefix -l, $(LIB_NAME)) $(3TH)
DEP = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(3TH) $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): lib"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(NAME):"
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(3TH_PATH)/%.a:
	@$(MAKE) -C $(shell dirname $@)

clean:
	@rm -rf $(OBJ_PATH)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

-include $(DEP)

.PHONY: all, $(NAME), clean, fclean, re
