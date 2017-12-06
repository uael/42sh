# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/05 15:07:01 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Werror -Wextra -Wall -O3

SRC_PATH = ./src/
OBJ_PATH = ./obj/
SOB_PATH = cty/ ds/ fs /int/ io/ lex/ lib/ math/ mem/ str/ trm/
3TH_PATH =
INC_PATH = ./include/ $(addprefix $(3TH_PATH), include/)
LNK_PATH = ./ $(3TH_PATH)

OBJ_NAME = $(SRC_NAME:.c=.o)
3TH_NAME = ncurses
SRC_NAME = \
	cty/ft_isalnum.c \
	cty/ft_isalpha.c \
	cty/ft_isascii.c \
	cty/ft_isdigit.c \
	cty/ft_islower.c \
	cty/ft_isprint.c \
	cty/ft_isspace.c \
	cty/ft_isupper.c \
	cty/ft_tolower.c \
	cty/ft_toupper.c \
	ds/ft_dstr_append.c \
	ds/ft_dstr_at.c \
	ds/ft_dstr_begin.c \
	ds/ft_dstr_ctor.c \
	ds/ft_dstr_dtor.c \
	ds/ft_dstr_emplace.c \
	ds/ft_dstr_end.c \
	ds/ft_dstr_ensure.c \
	ds/ft_dstr_grow.c \
	ds/ft_dstr_pop.c \
	ds/ft_dstr_popn.c \
	ds/ft_dstr_prepend.c \
	ds/ft_dstr_push.c \
	ds/ft_dstr_pushc.c \
	ds/ft_dstr_pushn.c \
	ds/ft_dstr_pushnc.c \
	ds/ft_dstr_put.c \
	ds/ft_dstr_putc.c \
	ds/ft_dstr_putn.c \
	ds/ft_dstr_putnc.c \
	ds/ft_dstr_realloc.c \
	ds/ft_dstr_remove.c \
	ds/ft_dstr_removen.c \
	ds/ft_dstr_shift.c \
	ds/ft_dstr_shiftn.c \
	ds/ft_dstr_size.c \
	ds/ft_dstr_unshift.c \
	ds/ft_dstr_unshiftc.c \
	ds/ft_dstr_unshiftn.c \
	ds/ft_dstr_unshiftnc.c \
	ds/ft_vi_at.c \
	ds/ft_vi_begin.c \
	ds/ft_vi_ctor.c \
	ds/ft_vi_dtor.c \
	ds/ft_vi_clear.c \
	ds/ft_vi_clean.c \
	ds/ft_vi_end.c \
	ds/ft_vi_ensure.c \
	ds/ft_vi_grow.c \
	ds/ft_vi_pop.c \
	ds/ft_vi_popn.c \
	ds/ft_vi_push.c \
	ds/ft_vi_pushc.c \
	ds/ft_vi_pushn.c \
	ds/ft_vi_pushnc.c \
	ds/ft_vi_put.c \
	ds/ft_vi_putc.c \
	ds/ft_vi_putn.c \
	ds/ft_vi_putnc.c \
	ds/ft_vi_realloc.c \
	ds/ft_vi_remove.c \
	ds/ft_vi_removen.c \
	ds/ft_vi_shift.c \
	ds/ft_vi_shiftn.c \
	ds/ft_vi_size.c \
	ds/ft_vi_unshift.c \
	ds/ft_vi_unshiftc.c \
	ds/ft_vi_unshiftn.c \
	ds/ft_vi_unshiftnc.c \
	ds/ft_vu_at.c \
	ds/ft_vu_begin.c \
	ds/ft_vu_clean.c \
	ds/ft_vu_clear.c \
	ds/ft_vu_ctor.c \
	ds/ft_vu_dtor.c \
	ds/ft_vu_end.c \
	ds/ft_vu_ensure.c \
	ds/ft_vu_grow.c \
	ds/ft_vu_pop.c \
	ds/ft_vu_popn.c \
	ds/ft_vu_push.c \
	ds/ft_vu_pushc.c \
	ds/ft_vu_pushn.c \
	ds/ft_vu_pushnc.c \
	ds/ft_vu_put.c \
	ds/ft_vu_putc.c \
	ds/ft_vu_putn.c \
	ds/ft_vu_putnc.c \
	ds/ft_vu_realloc.c \
	ds/ft_vu_remove.c \
	ds/ft_vu_removen.c \
	ds/ft_vu_shift.c \
	ds/ft_vu_shiftn.c \
	ds/ft_vu_size.c \
	ds/ft_vu_unshift.c \
	ds/ft_vu_unshiftc.c \
	ds/ft_vu_unshiftn.c \
	ds/ft_vu_unshiftnc.c \
	ds/ft_di_at.c \
	ds/ft_di_begin.c \
	ds/ft_di_ctor.c \
	ds/ft_di_dtor.c \
	ds/ft_di_clear.c \
	ds/ft_di_clean.c \
	ds/ft_di_end.c \
	ds/ft_di_ensure.c \
	ds/ft_di_grow.c \
	ds/ft_di_pop.c \
	ds/ft_di_popn.c \
	ds/ft_di_push.c \
	ds/ft_di_pushc.c \
	ds/ft_di_pushn.c \
	ds/ft_di_pushnc.c \
	ds/ft_di_put.c \
	ds/ft_di_putc.c \
	ds/ft_di_putn.c \
	ds/ft_di_putnc.c \
	ds/ft_di_realloc.c \
	ds/ft_di_remove.c \
	ds/ft_di_removen.c \
	ds/ft_di_shift.c \
	ds/ft_di_shiftn.c \
	ds/ft_di_size.c \
	ds/ft_di_unshift.c \
	ds/ft_di_unshiftc.c \
	ds/ft_di_unshiftn.c \
	ds/ft_di_unshiftnc.c \
	ds/ft_du_at.c \
	ds/ft_du_begin.c \
	ds/ft_du_clean.c \
	ds/ft_du_clear.c \
	ds/ft_du_ctor.c \
	ds/ft_du_dtor.c \
	ds/ft_du_end.c \
	ds/ft_du_ensure.c \
	ds/ft_du_grow.c \
	ds/ft_du_pop.c \
	ds/ft_du_popn.c \
	ds/ft_du_push.c \
	ds/ft_du_pushc.c \
	ds/ft_du_pushn.c \
	ds/ft_du_pushnc.c \
	ds/ft_du_put.c \
	ds/ft_du_putc.c \
	ds/ft_du_putn.c \
	ds/ft_du_putnc.c \
	ds/ft_du_realloc.c \
	ds/ft_du_remove.c \
	ds/ft_du_removen.c \
	ds/ft_du_shift.c \
	ds/ft_du_shiftn.c \
	ds/ft_du_size.c \
	ds/ft_du_unshift.c \
	ds/ft_du_unshiftc.c \
	ds/ft_du_unshiftn.c \
	ds/ft_du_unshiftnc.c \
	ds/ft_node.c \
	ds/ft_node_add.c \
	ds/ft_node_next.c \
	ds/ft_node_prev.c \
	exe/ft_job.c \
	exe/ft_job_exe.c \
	exe/ft_job_run.c \
	exe/ft_worker.c \
	fs/ft_basename.c \
	fs/ft_isdots.c \
	fs/ft_pathjoin.c \
	fs/ft_pathreal.c \
	int/ft_intlen.c \
	int/ft_intstr.c \
	io/ft_cin_read.c \
	io/ft_cin_seek.c \
	io/ft_cout_write.c \
	io/ft_cout_seek.c \
	io/ft_ifstream.c \
	io/ft_ifstream_peek.c \
	io/ft_ifstream_read.c \
	io/ft_ifstream_seek.c \
	io/ft_imstream.c \
	io/ft_imstream_peek.c \
	io/ft_imstream_read.c \
	io/ft_imstream_seek.c \
	io/ft_istream.c \
	io/ft_istream_peek.c \
	io/ft_istream_read.c \
	io/ft_istream_seek.c \
	io/ft_ofstream.c \
	io/ft_ofstream_put.c \
	io/ft_ofstream_write.c \
	io/ft_ofstream_seek.c \
	io/ft_omstream.c \
	io/ft_omstream_put.c \
	io/ft_omstream_write.c \
	io/ft_omstream_seek.c \
	io/ft_ostream.c \
	io/ft_ostream_put.c \
	io/ft_ostream_write.c \
	io/ft_ostream_seek.c \
	io/ft_padn.c \
	io/ft_putc.c \
	io/ft_putf.c \
	io/ft_putl.c \
	io/ft_putn.c \
	io/ft_puts.c \
	lex/lexer.c \
	lex/lexer_peek.c \
	lex/lexer_scan.c \
	lex/src.c \
	lex/src_peek.c \
	lex/tok.c \
	lex/tokv_dtor.c \
	lex/tokv_init0.c \
	lex/tokv_init1.c \
	lex/tokv_init2.c \
	lib/ft_atoi.c \
	lib/ft_clean.c \
	lib/ft_dtor.c \
	lib/ft_getenv.c \
	lib/ft_itoa.c \
	lib/ft_join.c \
	lib/ft_strerr.c \
	math/ft_imax.c \
	math/ft_imin.c \
	math/ft_pow.c \
	math/ft_pow2_next.c \
	math/ft_umax.c \
	math/ft_umin.c \
	mem/ft_calloc.c \
	mem/ft_malloc.c \
	mem/ft_realloc.c \
	str/ft_bzero.c \
	str/ft_memccpy.c \
	str/ft_memchr.c \
	str/ft_memcmp.c \
	str/ft_memcpy.c \
	str/ft_memmove.c \
	str/ft_memrcpy.c \
	str/ft_memset.c \
	str/ft_strbegw.c \
	str/ft_strcat.c \
	str/ft_strchr.c \
	str/ft_strclr.c \
	str/ft_strcmp.c \
	str/ft_strcpy.c \
	str/ft_strdup.c \
	str/ft_strlcat.c \
	str/ft_strlen.c \
	str/ft_strnbr.c \
	str/ft_strncat.c \
	str/ft_strncmp.c \
	str/ft_strncpy.c \
	str/ft_strnlen.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strstr.c \
	trm/ft_caps.c \
	trm/ft_trm.c \
	trm/ft_trm_on.c \
	trm/ft_trm_keys.c

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
SOB = $(addprefix $(OBJ_PATH), $(SOB_PATH))
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
	@echo  "$(NAME): lib \033[32m[✔]\033[0m"

$(EXE): 3th $(OBJ)
	@$(CC) $(CFLAGS) $(LNK) $(3TH) $(INC) $(OBJ) -o $(NAME)
	@echo  "$(NAME): exe \033[32m[✔]\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	@echo "$(NAME): \033[34m[$<]\033[0m"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "\033[A\033[K\033[A"

clean:
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) clean
endif
	@rm -rf $(OBJ_PATH)
	@echo "$(NAME): $@ \033[32m[✔]\033[0m"

fclean: clean
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) fclean
endif
	@rm -f $(NAME)
	@echo "$(NAME): $@ \033[32m[✔]\033[0m"

3th:
ifneq ($(3TH_PATH),)
	@$(MAKE) -C $(3TH_PATH) -j4
endif

norm:
	@./norm.sh $(shell find $(SRC_PATH) $(INC_PATH) -name '*.h' -o -name '*.c')

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
