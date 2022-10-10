NAME= a.out
CC= cc
FLAGMLX= -lm -lbsd -lmlx -lXext -lX11
CFLAGS= -Wall -Wextra -Werror
SRCS = main.c
OBJS = ${SRCS:.c=.o}
RM = rm -rf
LIB = libft/libft.a

all: ${NAME}

${NAME}: ${OBJS} ${LIB}
	${CC} -g3 ${OBJS} ${LIB} -o ${NAME} ${FLAGMLX}

%.o: %.c
	${CC} -g3 -c $< -o $@

${LIB}:
	make -C libft

clean:
	${RM} ${OBJS}
	make -C libft/ clean

fclean: clean
	${RM} ${NAME}
	make -C libft/ fclean

re: fclean all