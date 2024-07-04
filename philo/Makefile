# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 14:40:02 by tguerran          #+#    #+#              #
#    Updated: 2024/07/05 00:52:18 by tguerran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread

SRC = philo.c \
		utils/utils.c \
		init.c \
		error/error.c \
		error/error2.c \
		utils/utils2.c \
		free.c \
		parse.c \
		utils/utils3.c \
		main.c \
		routine.c
		

OFILES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o  $(NAME) $(OFILES)
	
clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)