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
RCFLAGS = $(WFLAGS) -O2 -fsanitize=address
CC ?= gcc

INC_PATH = include
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH = vendor

LIB_NAME = ps rl ft
3TH_NAME = libft librl libps
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c bi/history.c bi/read.c\
	comp.c \
	env.c \
	err.c \
	eval.c eval/assign.c eval/compound.c eval/func.c eval/ifclause.c \
	eval/operator.c eval/redir.c eval/redir_1.c eval/whileclause.c eval/word.c \
	exp.c exp/backslash.c exp/backtick.c exp/brace.c exp/dollars.c \
	exp/glob.c exp/quote.c exp/tilde.c \
	exp/arith.c exp/arith/eval.c \
	exp/comm.c exp/comm/read.c \
	exp/param.c exp/param/env.c exp/param/subst.c exp/param/val.c \
	func.c \
	lex.c lex/dollar.c lex/heredoc.c lex/line.c lex/op.c lex/reduce.c \
	lex/utils.c lex/word.c \
	main.c \
	prompt.c \
	shell.c \
	syn.c syn/andor.c syn/cmd.c syn/compound.c syn/funcdef.c syn/ifclause.c \
	syn/list.c syn/pipe.c syn/redir.c syn/term.c syn/whileclause.c \
	tok.c \
	var.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

PRINTF=test $(VERBOSE)$(TRAVIS) || printf
3DE = $(shell echo "$(3TH_NAME)" | sed -E "s|([\.a-zA-Z]+)|$(3TH_PATH)/\1/\1.a|g")

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	@$(PRINTF) "%-20s" "$(PROJECT): exe"
	+$(MAKE) -j4 $(PROJECT) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"
	@$(PRINTF) "\r\x1b[20C\x1b[0K\x1b[32m✔\x1b[0m\n"

$(PROJECT): $(3DE) $(OBJ)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	$(CC) $(CFLAGS) $(INC) $(LNK) $(OBJ) $(LIB) -o $(PROJECT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$<"
	$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(dir $(OBJ))

clean:
	rm -rf $(OBJ_DIR)
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	rm -f $(PROJECT)
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

re: clean all

test: all
	./test.sh . $(PROJECT)

-include $(DEP)

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif

.PHONY: all, $(PROJECT), clean, fclean, re, test
