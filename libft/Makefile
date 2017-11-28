# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/11/18 09:54:36 by null             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = libft
NAME = $(PROJECT).a
CC = gcc
CFLAGS += -Wall -Werror -Wextra -O3

SRC_PATH = ./src/
INC_PATH = ./include/
OBJ_PATH = ./obj/
OBJ_PATHS = cty ds fs int io lex lib math mem str

OBJ_SUB_PATHS = $(addprefix $(OBJ_PATH),$(OBJ_PATHS))
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

SRC_NAME += \
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
	ds/ft_dstr_putf.c \
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
	fs/ft_basename.c \
	fs/ft_isdots.c \
	fs/ft_pathjoin.c \
	int/ft_intlen.c \
	int/ft_intstr.c \
	io/ft_cin_read.c \
	io/ft_cin_seek.c \
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
	lib/ft_dtor.c \
	lib/ft_itoa.c \
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
	str/ft_strstr.c

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_SUB_PATHS)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	ar -rc $(NAME) $?
	ranlib $(NAME)

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
