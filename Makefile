# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/20 12:04:56 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT ?= 42sh
WFLAGS = -Werror -Wextra -Wall
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls -Wall -Werror -Wextra
RCFLAGS = $(WFLAGS) -O2 -fomit-frame-pointer
DCFLAGS = $(WFLAGS) -g3 -DDEBUG
SCFLAGS = -fsanitize=address,undefined -ferror-limit=5 $(DCFLAGS)
CC ?= gcc
MAKE += -j4

INC_PATH = include
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH = vendor

LIBS = ps rl ft
ifneq (,$(findstring dev,$(PROJECT)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(PROJECT)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME = libft librl libps
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c bi/history.c bi/read.c\
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/sep.c eval/simple.c eval/subshell.c \
	exp.c exp/backslash.c exp/backtick.c exp/brace.c exp/dollars.c \
	exp/glob.c exp/quote.c exp/tilde.c \
	exp/arith.c exp/arith/eval.c \
	exp/comm.c exp/comm/read.c \
	exp/param.c exp/param/env.c exp/param/subst.c exp/param/val.c \
	lex.c lex/check.c lex/heredoc.c lex/op.c lex/reduce.c lex/utils.c \
	lex/dollar.c lex/word.c \
	main.c \
	prompt.c \
	shell.c \
	tok.c \
	var.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

ifneq (,$(findstring dev,$(PROJECT)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.dev.a|g")
else ifneq (,$(findstring san,$(PROJECT)))
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.san.a|g")
else
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.a|g")
endif

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	+$(MAKE) $(PROJECT) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	+$(MAKE) $(PROJECT).dev "PROJECT = $(PROJECT).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
endif
	+$(MAKE) $(PROJECT).san "PROJECT = $(PROJECT).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

mecry:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) mecry &&) true
endif
	+$(MAKE) $(PROJECT) "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

$(PROJECT): $(3DE) $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJ) $(LIB) -o $(PROJECT)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(PROJECT): exe"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(PROJECT):"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

clean:
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs rmdir || true
	rm -f $(PROJECT){,.san,.dev}
	@printf  "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

re: clean all

test: all
	./test.sh . $(PROJECT)

testdev: dev
	./test.sh . $(PROJECT).dev

testsan: san
	./test.sh . $(PROJECT).san

valgrind: dev
	./valgrind.sh . $(PROJECT).dev

-include $(DEP)

ifndef VERBOSE
.SILENT:
endif

.PHONY: all, dev, san, mecry, $(PROJECT), clean, fclean, re, test, testdev, \
  testsan, valgrind
