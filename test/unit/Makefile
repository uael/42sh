#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2018/02/09 10:54:12 by mc               ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		flextest3000

C_NAME =	main.c	test_env.c
C_GLOB =    test_glob.c

ROOT_DIR =	../..
O_DIR =		obj
VPATH =		src						src/glob

SRCS =		$(C_NAME)				$(C_GLOB)

OBJS =		$(SRCS:%.c=$(O_DIR)/%.o)
TEST_OBJS =	$(shell find $(ROOT_DIR)/obj/rel -name \*.o 2>/dev/null | grep -v main) #TODO
DEPS =		$(OBJS:%.o=%.d)

LFT_DIR =	$(ROOT_DIR)/vendor/libft
LFT_I_DIR = -I$(LFT_DIR)/include
LFT =		$(LFT_DIR)/libft.a
LFT_LIB =	-L$(LFT_DIR) -lft

LRL_DIR =	$(ROOT_DIR)/vendor/librl
LRL_I_DIR = -I$(LRL_DIR)/include
LRL =		$(LRL_DIR)/librl.a
LRL_LIB =	-L$(LRL_DIR) -lrl

LPS_DIR =	$(ROOT_DIR)/vendor/libps
LPS_I_DIR = -I$(LPS_DIR)/include
LPS =		$(LPS_DIR)/libps.a
LPS_LIB =	-L$(LPS_DIR) -lps

MIN_DIR =	minunit
MIN_I_DIR = -I$(MIN_DIR)
MIN =		$(MIN_DIR)/minunit.h
MIN_LIB =

I_DIR =		$(LFT_I_DIR)	$(LRL_I_DIR)	$(LPS_I_DIR)	$(MIN_I_DIR)	-Iinclude	-I$(ROOT_DIR)/include
LIBS =		$(LFT_LIB)		$(LRL_LIB)		$(LPS_LIB)		$(MIN_LIB)		-lm

RM =		rm -rf
MKDIR =		mkdir -p
CC =		$(shell clang --version >/dev/null 2>&1 && echo clang || echo gcc)
CFLAGS =	-Wall -Wextra -Werror -O2

UNAME_S =   $(shell uname -s)
ifeq ($(UNAME_S), Linux)
  ECHO =	echo -e
else ifeq ($(UNAME_S), Darwin)
  ECHO =	echo
endif

WHITE =		\033[37;01m
RED =		\033[31;01m
GREEN =		\033[32;01m
YELLOW =	\033[33;01m
BLUE =		\033[34;01m
BASIC =		\033[0m

ifndef VERBOSE
.SILENT:
endif


.PHONY: all debug sanitize me_cry clean fclean mrproper re

all:
	$(MAKE) -C $(ROOT_DIR) $(FLAGS)
	$(MAKE) $(NAME) $(FLAGS)
	./$(NAME)

debug: FLAGS = "CFLAGS = -D DEBUG -g -ggdb"
debug: all

sanitize: FLAGS = "CFLAGS = -D DEBUG -g -ggdb -fsanitize=address,undefined \
-ferror-limit=5"
sanitize: all

me_cry: FLAGS = "CFLAGS = -Wpedantic -Wshadow -Wconversion -Wcast-align \
-Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
-Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
-Waggregate-return -Wstrict-overflow=5 -Wold-style-definition  \
-Wredundant-decls -Wall -Werror -Wextra" #-Wcast-qual -Wpadded
me_cry: all

clean:
	$(RM) $(O_DIR)

fclean: clean
	$(RM) $(NAME)

mrproper: fclean
	$(MAKE) -C $(ROOT_DIR) fclean

re: fclean all


-include $(DEPS)

$(NAME): $(OBJS) $(LFT) $(LRL) $(LPS) $(MIN) $(TEST_OBJS)
	@$(ECHO) "$(BLUE)$(OBJS) $(TEST_OBJS)$(WHITE)->$(RED) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(CCFLAGS) $(I_DIR) $(OBJS) $(TEST_OBJS) -Wl,--allow-multiple-definition,--whole-archive $(LIBS) -Wl,--no-whole-archive -o $@
	@$(ECHO) "$(WHITE)cflags:$(BASIC) $(CFLAGS)"
	@$(ECHO) "$(WHITE)ccflags:$(BASIC) $(CCFLAGS)"
	@$(ECHO) "$(WHITE)libs:$(BASIC) $(LIBS)"
	@$(ECHO) "$(WHITE)compi:$(BASIC) $(CC)"

$(O_DIR)/%.o: %.c
	@$(ECHO) "$(WHITE)$<\t->$(BLUE) $@ $(BASIC)"
	$(CC) $(CFLAGS) $(CCFLAGS) $(I_DIR) -MMD -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
	$(MKDIR) $(O_DIR)
