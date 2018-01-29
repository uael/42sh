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

NAME = libft
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
INC_PATH = ./include/ $(addprefix $(3TH_PATH), include/)
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
R3TH_NAME =
D3TH_NAME = $(addsuffix .dev, $(R3TH_NAME))
S3TH_NAME = $(addsuffix .san, $(R3TH_NAME))
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
	get_opt/getoptlong.c get_opt/getoptlonglong.c get_opt/getopt.c \

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
EXE =
LIB = $(NAME)

all: $(LIB)

dev: $(LIB).dev

san: $(LIB).san

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
	@$(CC) $(DCFLAGS) $(INC) -MMD -MP -c $< -o $@
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

re: fclean all

redev: fcleandev dev

resan: fcleansan san

-include $(RDEP)
-include $(DDEP)
-include $(SDEP)

.PHONY: all, dev, san, 3th, $(NAME), clean, fclean, cleandev, fcleandev, \
  cleansan, fcleansan, re, redev, resan
