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
CFLAGS = -Werror -Wextra -Wall
RCFLAGS = $(CFLAGS) -O3
DCFLAGS = $(CFLAGS) -g3 -DDEBUG
SCFLAGS = $(DCFLAGS) -fsanitize=address

SRC_PATH = ./src/
OBJ_PATH = ./obj/
ROBJ_PATH = $(OBJ_PATH)rel/
DOBJ_PATH = $(OBJ_PATH)dev/
SOBJ_PATH = $(OBJ_PATH)san/
3TH_PATH = ./vendor/libft/ ./vendor/librl/
INC_PATH = ./include/
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
R3TH_NAME = rl ft
D3TH_NAME = $(addsuffix .dev, $(R3TH_NAME))
S3TH_NAME = $(addsuffix .san, $(R3TH_NAME))
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c bi/fg.c bi/bg.c bi/jobs.c \
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/sep.c eval/simple.c eval/subshell.c \
	job.c job/bg.c job/cont.c job/debug.c job/fg.c job/mark.c job/launch.c \
	job/state.c job/wait.c job/pipe.c \
	lex.c lex/heredoc.c lex/next.c lex/op.c lex/quote.c lex/var.c lex/tok.c \
	lex/word.c lex/reduce.c \
	main.c \
	pool.c pool/mark.c pool/notify.c \
	proc.c proc/bit.c proc/err.c proc/exe.c proc/fn.c proc/sh.c \
	prompt.c \
	redir.c \
	shell.c \
	tok.c \
	var.c \
	word.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
ROBJ = $(addprefix $(ROBJ_PATH), $(OBJ_NAME))
DOBJ = $(addprefix $(DOBJ_PATH), $(OBJ_NAME))
SOBJ = $(addprefix $(SOBJ_PATH), $(OBJ_NAME))
RDEP = $(ROBJ:%.o=%.d)
DDEP = $(DOBJ:%.o=%.d)
SDEP = $(SOBJ:%.o=%.d)
INC = $(addprefix -I, $(INC_PATH) $(addsuffix include/, $(3TH_PATH)))
LNK = $(addprefix -L, $(LNK_PATH))
R3TH = $(addprefix -l, $(R3TH_NAME))
D3TH = $(addprefix -l, $(D3TH_NAME))
S3TH = $(addprefix -l, $(S3TH_NAME))
EXE = $(NAME)
LIB =

all: $(EXE)

dev: $(EXE).dev

san: $(EXE).san

wut: all dev san

$(LIB).a: $(LIB)

$(LIB).dev.a: $(LIB).dev

$(LIB).san.a: $(LIB).san

$(LIB): 3th $(ROBJ)
	@ar -rc $(LIB).a $(ROBJ)
	@ranlib $(LIB).a
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(LIB): lib"

$(LIB).dev: 3thdev $(DOBJ)
	@ar -rc $(LIB).dev.a $(DOBJ)
	@ranlib $(LIB).dev.a
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(LIB).dev: lib"

$(LIB).san: 3thsan $(SOBJ)
	@ar -rc $(LIB).san.a $(SOBJ)
	@ranlib $(LIB).san.a
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(LIB).san: lib"

$(EXE): 3th $(ROBJ)
	@$(CC) $(RCFLAGS) $(LNK) $(INC) $(ROBJ) -o $(EXE) $(R3TH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(EXE): exe"

$(EXE).dev: 3thdev $(DOBJ)
	@$(CC) $(DCFLAGS) $(LNK) $(INC) $(DOBJ) -o $(EXE).dev $(D3TH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(EXE).dev: exe"

$(EXE).san: 3thsan $(SOBJ)
	@$(CC) $(SCFLAGS) $(LNK) $(INC) $(SOBJ) -o $(EXE).san $(S3TH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(EXE).san: exe"

$(ROBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME):"
	@$(CC) $(RCFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(DOBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME).dev:"
	@$(CC) $(RCFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(SOBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@printf  "\r%-25s\033[34m[$<]\033[0m\n" "$(NAME).san:"
	@$(CC) $(SCFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

clean:
	@rm -rf $(ROBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) fclean;)
endif
ifneq ($(LIB),)
	@rm -f $(LIB).a
else
	@rm -f $(EXE)
endif
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME): $@"

cleandev:
	@rm -rf $(DOBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME).dev: $@"

fcleandev: cleandev
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) fcleandev;)
endif
ifneq ($(LIB),)
	@rm -f $(LIB).dev.a
else
	@rm -f $(EXE).dev
endif
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME).dev: $@"

cleansan:
	@rm -rf $(SOBJ_PATH)
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME).san: $@"

fcleansan: cleansan
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) fcleansan;)
endif
ifneq ($(LIB),)
	@rm -f $(LIB).san.a
else
	@rm -f $(EXE).san
endif
	@printf  "%-25s\033[32m[✔]\033[0m\n" "$(NAME).san: $@"

3th:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib);)
endif

3thdev:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) dev;)
endif

3thsan:
ifneq ($(3TH_PATH),)
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) san;)
endif

test: all
	@./test.sh . 21sh

testdev: dev
	@./test.sh . 21sh.dev

testsan: san
	@./test.sh . 21sh.san

valgrind: all
	@valgrind --leak-check=full --track-origins=yes \
      --suppressions=./valgrind.supp ./21sh test/bi.sh 2>&1 | \
      grep "definitely lost:"
	@valgrind --leak-check=full --track-origins=yes \
      --suppressions=./valgrind.supp ./21sh test/cmd.sh 2>&1 | \
      grep "definitely lost:"
	@valgrind --leak-check=full --track-origins=yes \
      --suppressions=./valgrind.supp ./21sh test/heredoc.sh 2>&1 | \
      grep "definitely lost:"
	@valgrind --leak-check=full --track-origins=yes \
      --suppressions=./valgrind.supp ./21sh test/inhibitor.sh 2>&1 | \
      grep "definitely lost:"
	@valgrind --leak-check=full --track-origins=yes \
      --suppressions=./valgrind.supp ./21sh test/separator.sh 2>&1 | \
      grep "definitely lost:"

re: fclean all

redev: fcleandev dev

resan: fcleansan san

-include $(RDEP)
-include $(DDEP)
-include $(SDEP)

.PHONY: all, dev, san, 3th, 3thdev, 3thsan, $(NAME), clean, fclean, cleandev, \
  fcleandev, cleansan, fcleansan, re, redev, resan, test, testdev, testsan, \
  valgrind
