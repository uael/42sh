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

NAME ?= 42sh
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O2 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc
MAKE += -j4

INC_PATH = include
SRC_PATH = src
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
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c \
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/sep.c eval/simple.c eval/subshell.c \
	lex.c lex/heredoc.c lex/op.c lex/utils.c lex/var.c lex/word.c \
	main.c \
	prompt.c \
	shell.c \
	tok.c \
	var.c var/expand.c \
	word/explode.c word/resolve.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

all:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th);)
endif
	@+$(MAKE) $(NAME) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev;)
endif
	@+$(MAKE) $(NAME).dev "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san;)
endif
	@+$(MAKE) $(NAME).san "NAME = $(NAME).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJ) $(LIB) -o $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(NAME):"
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

clean:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) clean;)
endif
	@rm -rf $(OBJ_PATH)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean;)
endif
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

test: all
	@./test.sh . $(NAME)

testdev: dev
	@./test.sh . $(NAME).dev

testsan: san
	@./test.sh . $(NAME).san

valgrind: dev
	@./valgrind.sh . $(NAME).dev

-include $(DEP)

.PHONY: all, dev, san, $(NAME), clean, fclean, re, test, testdev, testsan, \
  valgrind
