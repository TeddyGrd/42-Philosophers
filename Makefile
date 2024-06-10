# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 14:40:02 by tguerran          #+#    #+#              #
#    Updated: 2024/06/10 21:26:44 by tguerran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

CC = cc
CFLAGS = -Wall -Werror -Wextra 

SRC = philo/philo.c \
		philo/utils.c \
		philo/init.c \
		philo/error.c \
		philo/error2.c \
		philo/utils2.c \
		philo/free.c \
		philo/parse.c \
		philo/utils3.c
		

OFILES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES)
	
clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)