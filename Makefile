# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 15:30:49 by sdemaude          #+#    #+#              #
#    Updated: 2024/02/16 17:07:08 by sdemaude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(SRC:.c=.o)
LIBDIR = libft
LIB = $(LIBDIR)/libft.a

SRC = pipex.c\
      pipex_utils.c

all : $(NAME)

$(LIB) : $(LIBDIR)
	make -C $(LIBDIR)

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f *.o
	make clean -C $(LIBDIR) 

fclean : clean
	rm -f $(NAME)
	rm -f $(LIB)

re : fclean all

c: all clean

.PHONY: all clean fclean re bonus c
