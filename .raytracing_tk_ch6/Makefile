SRCS = srcs/main.c \
	   srcs/raytracing.c \
	   srcs/scene_setting1.c \
	   srcs/vector_utils.c \
	   

OBJS = ${patsubst $(SRCS_DIR)%.c,  $(OBJS_DIR)%.o, $(SRCS)}

NAME = play
MLX = ../minilibx_macos/libmlx.a
CC	= cc
# CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = incs/

all: ${NAME} ${MLX} ;

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	mkdir -p $(@D)
	${CC} ${CFLAGS} -I $(INCS_DIR) -c $< -o $@

#gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
${NAME}: ${OBJS} ${MLX}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBFT} ${MLX} -framework OpenGL -framework AppKit 

${MLX}:
	make -C ../minilibx_macos

clean: 
	rm -rf ${OBJS_DIR}

fclean: clean
	make clean -C ../minilibx_macos
	rm -rf ${NAME}

re: fclean all ;

.PHONY: all clean fclean re 