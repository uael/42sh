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
CFLAGS = -Werror -Wextra -Wall -O2

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH = ../libft/
INC_PATH = ./include/ $(addprefix $(3TH_PATH), include/)
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
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

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))
LNK = $(addprefix -L, $(LNK_PATH))
3TH = $(addprefix -l, $(3TH_NAME))
EXE =
LIB = $(NAME)

all: $(EXE) $(LIB)

$(LIB): 3th $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): lib"

$(EXE): 3th $(OBJ)
	@$(CC) $(CFLAGS) $(LNK) $(INC) $(OBJ) -o $(NAME) $(3TH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME):"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\033[A\033[2K"

clean:
	@rm -rf $(OBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) fclean;)
endif
	@rm -f $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

3th:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) -j4;)
endif

re: fclean all

.PHONY: all, 3th, $(NAME), clean, fclean, re
