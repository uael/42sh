# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/10 16:31:20 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME ?= 42sh
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O3 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc
MAKE += -j4

INC_PATH = include
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH = vendor

LIBS = ps rl ft
ifneq (,$(findstring dev,$(NAME)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(NAME)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME = libft librl libps
SRC_NAME = \
	bi.c cd.c echo.c bi_env.c exit.c \
	export.c setenv.c unset.c unsetenv.c \
	comp.c \
	env.c \
	err.c \
	eval.c ampr.c andor.c argv.c assign.c cmd.c \
	cmp.c compound.c heredoc.c lamp.c list.c \
	pipeline.c ramp.c raout.c redir.c rin.c \
	rout.c sep.c simple.c subshell.c \
	lex.c lex_heredoc.c op.c utils.c lex_var.c word.c \
	main.c \
	prompt.c \
	shell.c \
	tok.c \
	var.c expand.c \
	explode.c resolve.c

VPATH = src src/bi src/eval src/lex src/var src/word
3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th);)
endif
	+$(MAKE) $(NAME) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev;)
endif
	+$(MAKE) $(NAME).dev "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san;)
endif
	+$(MAKE) $(NAME).san "NAME = $(NAME).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

$(NAME): $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJ) $(LIB) -o $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)/%.o: %.c
	@printf "\r%-20s$<\n" "$(NAME):"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) clean;)
endif
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean;)
endif
	test -d $(OBJ_DIR)/rel && rmdir $(OBJ_DIR)/rel || true
	test -d $(OBJ_DIR)/dev && rmdir $(OBJ_DIR)/dev || true
	test -d $(OBJ_DIR)/san && rmdir $(OBJ_DIR)/san || true
	test -d $(OBJ_DIR) && rmdir $(OBJ_DIR) || true
	rm -f $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

test: all
	./test.sh . $(NAME)

testdev: dev
	./test.sh . $(NAME).dev

testsan: san
	./test.sh . $(NAME).san

valgrind: dev
	./valgrind.sh . $(NAME).dev

-include $(DEP)

ifndef VERBOSE
.SILENT:
endif

.PHONY: all, dev, san, $(NAME), clean, fclean, re, test, testdev, testsan, \
  valgrind
