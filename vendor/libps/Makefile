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

NAME = libps.a
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fno-omit-frame-pointer -fsanitize=address

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include ../libft/include ../librl/include
3TH_PATH =

LIB_NAME =
3TH_NAME =
SRC_NAME = \
	bi/fg.c bi/bg.c bi/jobs.c \
	job.c job/bg.c job/cont.c job/debug.c job/fg.c job/mark.c job/launch.c \
	job/state.c job/wait.c job/pipe.c \
	pool.c pool/mark.c pool/notify.c \
	proc.c proc/bi.c proc/bit.c proc/err.c proc/exe.c proc/fn.c proc/fork.c \
	ps.c \
	redir.c

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
INC = $(addprefix -I, $(INC_PATH))
3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
LIB = $(addprefix -l, $(LIB_NAME)) $(3TH)
DEP = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(3TH) $(OBJ)
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): lib"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(shell dirname $@)
	@printf "\r%-20s$<\n" "$(NAME):"
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@
	@printf "\033[A\033[2K"

$(3TH_PATH)/%.a:
	@$(MAKE) -C $(shell dirname $@)

clean:
	@rm -rf $(OBJ_PATH)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@printf  "%-20s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

-include $(DEP)

.PHONY: all, $(NAME), clean, fclean, re
