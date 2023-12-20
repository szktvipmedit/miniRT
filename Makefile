SRCS = srcs/main.c \
	   srcs/init_rt_info.c \
	   srcs/create_image.c \
	   srcs/create_image2.c \
	   srcs/raytracing/raytracing.c \
	   srcs/raytracing/get_nearest_shape.c \
	   srcs/raytracing/intersection_sphere.c \
	   srcs/raytracing/intersection_plane.c \
	   srcs/raytracing/radience.c \
	   srcs/error_messages.c \
	   srcs/scene_setting1.c \
	   srcs/utils/vector_utils.c \
	   srcs/utils/color_utils.c \
	   

OBJS = ${patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o, $(SRCS)}

NAME = miniRT
LIBFT = libft/libft.a
MLX = minilibx_macos/libmlx.a
CC	= cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = incs/

all: ${NAME} ${MLX} ;

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} -I $(INCS_DIR) -c $< -o $@

#gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
${NAME}: ${LIBFT} ${OBJS} ${MLX}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBFT} ${MLX} -framework OpenGL -framework AppKit 

${LIBFT}:
	make -C libft

${MLX}:
	make -C minilibx_macos

clean: 
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${OBJS_DIR}

fclean: clean
	make clean -C minilibx_macos
	rm -rf ${NAME}

re: fclean all ;

.PHONY: all clean fclean re 