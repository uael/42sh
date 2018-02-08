# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/11 12:29:40 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME ?= libft
CFLAGS += -Werror -Wextra -Wall
RCFLAGS = -O3 -fomit-frame-pointer
DCFLAGS = -g3 -DDEBUG
SCFLAGS = -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc

INC_PATH = include
SRC_PATH = src
OBJ_PATH ?= obj
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
	cty/cty.c cty/cty_2.c cty/cty_3.c \
	ds/alloc.c ds/apd.c ds/at.c ds/aver.c ds/back.c ds/begin.c ds/clean.c \
	ds/clr.c ds/cpush.c ds/cput.c ds/ctor.c ds/cusht.c ds/dtor.c ds/emp.c \
	ds/end.c ds/grow.c ds/len.c ds/mpush.c ds/mput.c ds/musht.c ds/npop.c \
	ds/npush.c ds/nput.c ds/nrem.c ds/nsht.c ds/nusht.c ds/pop.c ds/prd.c \
	ds/push.c ds/put.c ds/rem.c ds/sht.c ds/usht.c ds/mdtor.c ds/map.c \
	ds/map_2.c ds/set.c ds/set_2.c \
	ex/ex.c ex/ex_2.c \
	fs/fs.c fs/fs_2.c fs/fs_3.c fs/fs_4.c \
	hash/hash.c hash/hash_2.c \
	int/len.c int/str.c \
	io/fcntl.c io/ifs.c io/ifs_2.c io/ofs.c io/ofs_2.c io/ofs_3.c io/padn.c \
	io/putc.c io/putf.c io/putl.c io/putn.c io/puts.c \
	lib/atoi.c lib/clean.c lib/dtor.c lib/getenv.c lib/itoa.c lib/join.c \
	lib/strerr.c \
	math/imax.c math/imin.c math/m4.c math/m4_mul.c math/m4_rot.c \
	math/m4_trans.c math/pow.c math/pow2_next.c math/umax.c math/umin.c \
	math/v3.c math/v3_2.c math/eq.c math/eq_2.c \
	mem/alloc.c \
	str/mem.c str/mem_2.c str/str.c str/str_2.c str/str_3.c str/str_4.c \
	str/str_5.c \
	get_opt/getoptlong.c get_opt/getoptlonglong.c get_opt/getopt.c

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
	@+$(MAKE) $(NAME).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_PATH)/rel"

dev:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev;)
endif
	@+$(MAKE) $(NAME).dev.a "NAME = $(NAME).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_PATH)/dev"

san:
ifneq ($(3TH_NAME),)
	@+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san;)
endif
	@+$(MAKE) $(NAME).san.a "NAME = $(NAME).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_PATH)/san"

$(NAME).a: $(OBJ)
	@ar -rc $(NAME).a $(OBJ)
	@ranlib $(NAME).a
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): lib"

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

-include $(DEP)

.PHONY: all, dev, san, $(NAME).a, clean, fclean, re
