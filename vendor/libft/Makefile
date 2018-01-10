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

NAME = libft.a
CC = gcc
CFLAGS = -Werror -Wextra -Wall -O2

SRC_PATH = ./src/
OBJ_PATH = ./obj/
3TH_PATH =
INC_PATH = ./include/ $(addprefix $(3TH_PATH), include/)
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = m
SRC_NAME = \
	cty/cty.c cty/cty_2.c cty/cty_3.c \
	ds/alloc.c ds/apd.c ds/at.c ds/aver.c ds/back.c ds/begin.c ds/clean.c \
	ds/clear.c ds/cpush.c ds/cput.c ds/ctor.c ds/cusht.c ds/dtor.c ds/emp.c \
	ds/end.c ds/grow.c ds/len.c ds/mpush.c ds/mput.c ds/musht.c ds/npop.c \
	ds/npush.c ds/nput.c ds/nrem.c ds/nsht.c ds/nusht.c ds/pop.c ds/prd.c \
	ds/push.c ds/put.c ds/rem.c ds/sht.c ds/usht.c ds/mdtor.c \
	ex/ex.c ex/ex_2.c \
	fs/fs.c fs/fs_2.c fs/fs_3.c fs/fs_4.c \
	hash/hash.c hash/hash_2.c \
	int/len.c int/str.c \
	io/fcntl.c io/ifs.c io/ofs.c io/padn.c io/putc.c io/putf.c io/putl.c \
	io/putn.c io/puts.c \
	lib/atoi.c lib/clean.c lib/dtor.c lib/getenv.c lib/itoa.c lib/join.c \
	lib/strerr.c \
	math/imax.c math/imin.c math/m4.c math/m4_mul.c math/m4_rot.c \
	math/m4_trans.c math/pow.c math/pow2_next.c math/umax.c math/umin.c \
	math/v3.c math/v3_2.c math/eq.c math/eq_2.c \
	mem/alloc.c \
	str/mem.c str/mem_2.c str/str.c str/str_2.c str/str_3.c str/str_4.c \
	str/str_5.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))
LNK = $(addprefix -L, $(LNK_PATH))
3TH = $(addprefix -l, $(3TH_NAME))
EXE =
LIB = $(NAME)

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
	@$(foreach lib,$(3TH_PATH),$(MAKE) -C $(lib) -j4;)
endif

re: fclean all

.PHONY: all, 3th, $(NAME), clean, fclean, re
