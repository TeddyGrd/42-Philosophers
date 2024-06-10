# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 14:40:02 by tguerran          #+#    #+#              #
#    Updated: 2024/06/07 17:28:41 by tguerran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

CFLAGS = -Wall -Werror -Wextra 

SRC = philo/philo.c \
		philo/utils.c \
		philo/init.c \
		

OFILES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)
	
clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)