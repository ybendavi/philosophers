NAME = philo
CC = gcc
RM = rm -rf
SRCSDIR = srcs
OBJSDIR = objs
SRCS = main.c libfunc.c check_arg.c philosopher.c philo_init.c freer.c checker.c eat.c philo_action.c
OBJS = ${SRCS:%.c=${OBJSDIR}/%.o}
$(NAME): ${OBJS}
	$(CC) $(OBJS) -Wall -Wextra -Werror -lpthread -o ${NAME}
${OBJS}: ${OBJSDIR}/%.o: ${SRCSDIR}/%.c
	mkdir -p ${OBJSDIR}
	$(CC) -Wall -Wextra -Werror -I./includes -g -c $< -o $@

all: ${NAME}

clean: 
	${RM} ${OBJS}
	${RM} ${OBJSDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean all fclean re
