SRCS        = cub.c raycast.c raycast_utils.c movement.c textures.c press_release.c sprites.c sprites_utils.c check_start.c parse_resolution.c parse_colour.c parse_map.c parse_map_utils.c parse_textures.c ./gnl/get_next_line.c
OBJS        = ${SRCS:.c=.o}
NAME        = cub3D
CC          = cc
RM          = rm -f
#CFLAGS      = -Wall -Werror -Wextra
FRAMEWORK   = -lz -L . -lmlx -lft -framework OpenGL -framework AppKit
.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}
${NAME}:    ${OBJS}
			${MAKE} -C ./minilibx
			${MAKE} -C ./libft
			mv ./minilibx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}
all:        ${NAME}
clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./minilibx
			${MAKE} clean -C ./libft
fclean :    clean
			${RM} ${NAME} libmlx.a libft.a
re:         fclean all
.PHONY:     re all clean fclean
