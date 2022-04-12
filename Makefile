SRCS        = srcs/cub.c srcs/raycast.c srcs/raycast_utils.c srcs/movement.c srcs/textures.c srcs/press_release.c srcs/sprites.c srcs/sprites_utils.c srcs/check_start.c srcs/parse_resolution.c srcs/parse_colour.c srcs/parse_map.c srcs/parse_map_utils.c srcs/parse_textures.c srcs/screenshot.c ./gnl/get_next_line.c srcs/music.c
OBJS        = ${SRCS:.c=.o}
NAME        = cub3D
CC          = cc
RM          = rm -f
CFLAGS      = -Wall -Werror -Wextra
FRAMEWORK   = -lz -L . -lmlx -lft -framework OpenGL -framework AppKit
.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}
${NAME}:    ${OBJS}
			${MAKE} -C ./minilibx
			${MAKE} -C ./libft
			mv ./minilibx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -o ${NAME} ${OBJS} ${FRAMEWORK}
all:        ${NAME}
clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./minilibx
			${MAKE} clean -C ./libft
fclean :    clean
			${RM} ${NAME} libmlx.a libft.a
re:         fclean all
.PHONY:     re all clean fclean
