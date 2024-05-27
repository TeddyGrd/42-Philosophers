# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 14:40:02 by tguerran          #+#    #+#              #
#    Updated: 2024/05/27 17:56:39 by tguerran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

CFLAGS = -Wall -Werror -Wextra 

SRC = philo/philo.c \

OFILES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	
clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)