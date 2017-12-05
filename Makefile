# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/05 13:33:23 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
CFLAGS = -Werror -Wextra -Wall -O3

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH = ./libft/
INC_PATH = ./include/
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = ft ncurses
SRC_NAME = bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/setenv.c bi/unsetenv.c \
	bi.c cli.c env.c eval.c exe.c lex.c sh.c toks.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH) $(addprefix $(3TH_PATH), include/))
LNK = $(addprefix -L, $(LNK_PATH))
3TH = $(addprefix -l, $(3TH_NAME))
EXE = $(NAME)
LIB =

all: $(EXE) $(LIB)

$(LIB): 3th $(OBJ)
ifneq ($(filter %.o,$?),)
	@$(CC) $(CFLAGS) $(LNK) $(3TH) $(INC) $(filter %.o,$?) -o $(NAME)
	@ranlib $(NAME)
endif
	@echo  "$(NAME): \033[32m[✔]\033[0m"

$(EXE): 3th $(OBJ)
ifneq ($(filter %.o,$?),)
	@$(CC) $(CFLAGS) $(LNK) $(3TH) $(INC) $(filter %.o,$?) -o $(NAME)
endif
	@echo  "$(NAME): \033[32m[✔]\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@echo "$(NAME): \033[34m[$<]\033[0m"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "\033[A\033[K\033[A"

clean:
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) clean
endif
	@rm -rf $(OBJ_PATH)
	@echo "$(NAME): $@ \033[32m[✔]\033[0m"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) fclean
endif
	@rm -f $(NAME)
	@echo "$(NAME): $@ \033[32m[✔]\033[0m"

3th:
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) -j4
endif

norm:
	@./norm.sh $(shell find $(SRC_PATH) $(INC_PATH) -name '*.h' -o -name '*.c')

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
