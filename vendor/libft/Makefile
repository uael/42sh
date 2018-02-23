# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2018/02/23 20:22:09 by mcanal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT ?= libft
WFLAGS = -Werror -Wextra -Wall
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
-Wredundant-decls -Wall -Werror -Wextra  #-Wcast-qual
RCFLAGS = $(WFLAGS) -O2 -fomit-frame-pointer
DCFLAGS = $(WFLAGS) -g3 -DDEBUG
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc

INC_PATH = include
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH =

LIBS =
ifneq (,$(findstring dev,$(PROJECT)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(PROJECT)))
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
	glob/globux.c glob/glob_match.c glob/glob_climb_tree.c \
	glob/glob_util/glob_list.c glob/glob_util/glob_dir.c \
	glob/glob_util/glob_is_magic.c glob/glob_util/glob_path.c \
	glob/glob_util/glob_cmp.c glob/glob_util/glob_show.c \
	glob/glob_util/glob_brace.c \
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
	str/str_5.c str/str_6.c \
	getopt.c \
	sort/ft_shellsort.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

PRINTF=test $(VERBOSE)$(TRAVIS) || printf

ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	+$(MAKE) $(PROJECT).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	+$(MAKE) $(PROJECT).dev.a "PROJECT = $(PROJECT).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
endif
	+$(MAKE) $(PROJECT).san.a "PROJECT = $(PROJECT).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

mecry:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) mecry &&) true
endif
	+$(MAKE) $(PROJECT).a "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

$(PROJECT).a: $(OBJ)
	ar -rc $(PROJECT).a $(OBJ)
	ranlib $(PROJECT).a
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): lib"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(shell dirname $@)
	@$(PRINTF) "\r%-20s$<\n" "$(PROJECT):"
	$(CC) $(CFLAGS) $(CCFLAGS) $(INC) -MMD -MP -c $< -o $@
	@$(PRINTF) "\033[A\033[2K"

clean:
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs rmdir || true
	rm -f $(PROJECT){,.san,.dev}.a
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

re: clean all

-include $(DEP)

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif

.PHONY: all, dev, san, mecry, $(PROJECT).a, clean, fclean, re
