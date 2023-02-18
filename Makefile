NAME  = cub3D

SRCS  =  srcs/main.c srcs/vector.c srcs/test_suite.c srcs/camera.c srcs/color.c srcs/hit.c srcs/object.c srcs/sky.c srcs/container.c srcs/floor.c
OBJS  = ${SRCS:.c=.o}

HEADERS= includes/cub3d.h

CC= clang

CFLAGS= -Wall -Wextra -g3 

LIBFT= -L libft -lft

VALGRIND = colour-valgrind 

MLX            = mlx/libmlx.a mlx/libmlx_Darwin.a 

all: 		lib ${NAME} 

${NAME}: 	${OBJS}
				${CC} ${CFLAGS} -L /usr/lib ${OBJS} ${LIBFT} ${MLX} -lXext -lX11 -lm -lz -o ${NAME}

.c.o:
				${CC} ${CFLAGS} -I/usr/include -I${HEADERS} -Imlx -O3 -c $< -o $@

lib:
				make -C libft
				make -C mlx

clean:
				rm -f ${OBJS} 
							make -C libft clean
							make -C mlx clean

fclean:clean
				rm -f ${NAME}
							make -C libft fclean
							make -C mlx fclean

re:fclean all

norm:
				norminette -R CheckSourceHeader ${SRCS}

.PHONY :all clean fclean re norm 
