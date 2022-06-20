# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 17:31:34 by vfiszbin          #+#    #+#              #
#    Updated: 2022/06/20 16:22:36 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	philo.c\
		states.c\
		init_params_and_philos.c\
		utils.c\

OBJS = ${SRCS:.c=.o}

INCLUDES = philo.h

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

LIBS = -pthread

.c.o: ${INCLUDES}
	${CC} ${FLAGS} -c $ $< -o ${<:.c=.o}

all: ${NAME}

${NAME} : ${OBJS}
	
	${CC} ${FLAGS} ${OBJS} -o ${NAME} ${LIBS}

clean:
	${RM} *.o

fclean: clean
	${RM} so_long

re: fclean all

.PHONY: all clean fclean re