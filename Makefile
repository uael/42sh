# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/08 09:48:05 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -DDEBUG

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH = ./libft/
INC_PATH = ./include/
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = ft ncurses
SRC_NAME = \
	lex/op.c lex/skip.c lex/syn.c lex/word.c \
	eval/bi.c eval/bi/utils.c eval/bi/cd.c eval/bi/echo.c eval/bi/env.c \
	eval/bi/exit.c eval/bi/setenv.c eval/bi/unsetenv.c \
	eval.c eval/cmd.c eval/heredoc.c eval/pipe.c eval/rin.c eval/rout.c \
	eval/raout.c eval/sep.c eval/lamp.c eval/ramp.c \
	keys.c keys/down.c keys/left.c keys/return.c keys/right.c keys/up.c \
	reduce.c reduce/heredoc.c \
	cli.c env.c history.c lex.c sh.c tc.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH) $(addprefix $(3TH_PATH), include/))
LNK = $(addprefix -L, $(LNK_PATH))
3TH = $(addprefix -l, $(3TH_NAME))
EXE = $(NAME)
LIB =

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
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) clean
endif
	@rm -rf $(OBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) fclean
endif
	@rm -f $(NAME)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

3th:
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) -j4
endif

norm:
	@./norm.sh $(shell find $(SRC_PATH) $(INC_PATH) -name '*.h' -o -name '*.c')

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
