# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/10 17:12:52 by mc               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME ?= libft
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O3 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc

INC_PATH = include
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
	cty.c cty_2.c cty_3.c \
	ds_alloc.c apd.c at.c aver.c back.c begin.c ds_clean.c \
	clr.c cpush.c cput.c ctor.c cusht.c ds_dtor.c emp.c \
	end.c grow.c ds_len.c mpush.c mput.c musht.c npop.c \
	npush.c nput.c nrem.c nsht.c nusht.c pop.c prd.c \
	push.c put.c rem.c sht.c usht.c mdtor.c map.c \
	map_2.c set.c set_2.c \
	ex.c ex_2.c \
	fs.c fs_2.c fs_3.c fs_4.c \
	hash.c hash_2.c \
	len.c int_str.c \
	fcntl.c ifs.c ifs_2.c ofs.c ofs_2.c ofs_3.c padn.c \
	putc.c putf.c putl.c putn.c puts.c \
	atoi.c clean.c dtor.c getenv.c itoa.c join.c \
	strerr.c \
	imax.c imin.c m4.c m4_mul.c m4_rot.c \
	m4_trans.c pow.c pow2_next.c umax.c umin.c \
	v3.c v3_2.c eq.c eq_2.c \
	alloc.c \
	mem.c mem_2.c str.c str_2.c str_3.c str_4.c \
	str_5.c \
	getoptlong.c getoptlonglong.c getopt.c

VPATH = src src/cty src/get_opt src/lib src/ex src/io src/fs src/mem \
		src/str src/int src/math src/hash src/ds
3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	+$(MAKE) $(NAME).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	+$(MAKE) $(NAME).dev.a "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
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
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	test -d $(OBJ_DIR)/rel && rmdir $(OBJ_DIR)/rel || true
	test -d $(OBJ_DIR)/dev && rmdir $(OBJ_DIR)/dev || true
	test -d $(OBJ_DIR)/san && rmdir $(OBJ_DIR)/san || true
	test -d $(OBJ_DIR) && rmdir $(OBJ_DIR) || true
	rm -f $(NAME){,.san,.dev}.a
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

-include $(DEP)

ifndef VERBOSE
.SILENT:
endif

.PHONY: all, dev, san, $(NAME).a, clean, fclean, re
