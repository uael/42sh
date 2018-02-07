# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/12/08 09:48:05 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CC = gcc
CFLAGS = -Werror -Wextra -Wall -O3

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include vendor/libft/include vendor/librl/include vendor/libps/include
3TH_PATH = vendor

LIB_NAME =
3TH_NAME = libft/libft.a librl/librl.a libps/libps.a
SRC_NAME = \
	bi.c bi/cd.c bi/echo.c bi/env.c bi/exit.c bi/export.c bi/setenv.c \
	bi/unset.c bi/unsetenv.c \
	comp.c \
	env.c \
	err.c \
	eval.c eval/ampr.c eval/andor.c eval/argv.c eval/assign.c eval/cmd.c \
	eval/cmp.c eval/compound.c eval/heredoc.c eval/lamp.c eval/list.c \
	eval/pipeline.c eval/ramp.c eval/raout.c eval/redir.c eval/rin.c \
	eval/rout.c eval/sep.c eval/simple.c eval/subshell.c \
	lex.c lex/heredoc.c lex/op.c lex/utils.c lex/var.c lex/word.c \
	main.c \
	prompt.c \
	shell.c \
	tok.c \
	var.c var/expand.c \
	word/explode.c word/resolve.c

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
INC = $(addprefix -I, $(INC_PATH))
3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
LIB = $(addprefix -l, $(LIB_NAME)) $(3TH)
DEP = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(3TH) $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): exe"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(NAME):"
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(3TH_PATH)/%.a:
	@$(MAKE) -C $(shell dirname $@)

clean:
	@$(MAKE) -C $(3TH_PATH)/libft clean
	@$(MAKE) -C $(3TH_PATH)/librl clean
	@$(MAKE) -C $(3TH_PATH)/libps clean
	@rm -rf $(OBJ_PATH)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean:
	@$(MAKE) -C $(3TH_PATH)/libft fclean
	@$(MAKE) -C $(3TH_PATH)/librl fclean
	@$(MAKE) -C $(3TH_PATH)/libps fclean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

test: all
	@./test.sh . $(NAME)

valgrind: all
	@./valgrind.sh . $(NAME)

-include $(DEP)

.PHONY: all, $(NAME), clean, fclean, re, test, valgrind
