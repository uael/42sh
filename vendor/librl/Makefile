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
CFLAGS = -Werror -Wextra -Wall -g3 -DDEBUG

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH = ../libft/
INC_PATH = ./include/ $(addprefix $(3TH_PATH), include/)
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = ft
SRC_NAME = \
	rl_utf8.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix include/, $(3TH_PATH)))
LNK = $(addprefix -L, $(LNK_PATH))
3TH = $(addprefix -l, $(3TH_NAME))
EXE =
LIB = $(NAME)

all: $(EXE) $(LIB)

$(LIB): lib $(OBJ)
	ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): lib"

$(EXE): lib $(OBJ)
	@$(CC) $(CFLAGS) $(LNK) $(INC) $(OBJ) -o $(NAME) $(3TH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME):"
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf "\033[A\033[2K"

clean:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) clean;)
endif
	@rm -rf $(OBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) fclean;)
endif
	@rm -f $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

lib:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) -j4;)
endif

norm:
	@./norm.sh $(shell find $(SRC_PATH) $(INC_PATH) -name '*.h' -o -name '*.c')

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
