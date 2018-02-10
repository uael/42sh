# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/10 16:31:13 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME ?= libps
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O3 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc

INC_PATH = include ../libft/include ../librl/include
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH =

LIBS =
ifneq (,$(findstring dev,$(NAME)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(NAME)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME =
SRC_NAME = \
	fg.c bg.c jobs.c \
	job.c job_bg.c cont.c debug.c job_fg.c job_mark.c launch.c \
	state.c wait.c pipe.c \
	pool.c mark.c notify.c \
	proc.c bi.c bit.c err.c exe.c fn.c fork.c \
	ps.c \
	redir.c

VPATH = src src/bi src/pool src/proc src/job
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
	+$(MAKE) $(NAME).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev;)
endif
	+$(MAKE) $(NAME).dev.a "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san;)
endif
	+$(MAKE) $(NAME).san.a "NAME = $(NAME).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

$(NAME).a: $(OBJ_PATH) $(OBJ)
	ar -rc $(NAME).a $(OBJ)
	ranlib $(NAME).a
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): lib"

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

-include $(DEP)

ifndef VERBOSE
.SILENT:
endif

.PHONY: all, dev, san, $(NAME).a, clean, fclean, re
