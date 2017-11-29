# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vartyukh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/02 20:25:51 by vartyukh          #+#    #+#              #
#    Updated: 2017/04/02 20:25:53 by vartyukh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

IDIR = includes/

VPATH = src:includes

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

LIB = libft/libft.a

SRCS = 	main.c					\
		splitspaces.c			\
		read.c					\
		builtins.c				\
		get_next_line.c			\
		read2.c					\
		command_cd.c			\
		command_echo.c			\
		command_env.c			\
		command_setenv.c		\

all: $(NAME)

BINS = $(SRCS:.c=.o)

$(NAME): $(BINS)
	make -C libft/
	gcc -o $(NAME) $(BINS) $(LIB)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make clean -C libft/
	/bin/rm -f $(BINS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all
