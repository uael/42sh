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
CFLAGS = -Werror -Wextra -Wall -g3

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH = ./vendor/libft/ ./vendor/librl/
INC_PATH = ./include/
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = rl ft
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/set.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c bi/fg.c bi/bg.c bi/jobs.c \
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/simple.c eval/subshell.c \
	job.c job/bg.c job/cont.c job/debug.c job/fg.c job/mark.c job/launch.c \
	job/state.c job/wait.c job/pipe.c \
	lex.c lex/heredoc.c lex/next.c lex/op.c lex/quote.c lex/var.c lex/tok.c \
	lex/word.c lex/reduce.c \
	main.c \
	pool.c pool/mark.c pool/notify.c \
	proc.c proc/bit.c proc/err.c proc/exe.c proc/fn.c proc/sh.c \
	redir.c \
	shell.c \
	tok.c \
	var.c var/ifs.c \
	word.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix include/, $(3TH_PATH)))
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
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) -j8;)
endif

test: all
	./test.sh .

valgrind: all
	@valgrind --leak-check=full --track-origins=yes \
    --suppressions=./valgrind.supp ./21sh test/bi.sh 2>&1 | \
    grep "definitely lost:"
	@valgrind --leak-check=full --track-origins=yes \
    --suppressions=./valgrind.supp ./21sh test/cmd.sh 2>&1 | \
    grep "definitely lost:"

re: fclean all

.PHONY: all, 3th, $(NAME), clean, fclean, re, test, valgrind
