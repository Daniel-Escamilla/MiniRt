# Nombre del ejecutable
NAME = minirt

# Compilador y flags
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

# Directorio de fuentes
SRC_DIR = src

MAIN_SRC =      src/main/ft_main.c \
                src/main/ft_window.c \
                src/main/ft_initialize.c \

HOOKS_SRC =		src/hooks/ft_hooks.c \

RENDER_SRC =    src/render/ft_render.c \

# Archivos fuente
SRCS = 	$(MAIN_SRC) \
		$(HOOKS_SRC) \
		$(RENDER_SRC) \

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
# Directorio de archivos objeto
OBJDIR = $(NAME)_objects
# Directorio de la libft
LIBFT_DIR = ./libft
# Libreria a utilizar
LIBFT = $(LIBFT_DIR)/libft.a

# Directorio de MiniLibX
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

# Flags para MiniLibX
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/include/../lib -lXext -lX11 -lm

# Reglas
all: $(OBJDIR) libft mlx $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_FLAGS)

# Aquí no se requiere usar notdir
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJDIR):
	@mkdir -p $(OBJDIR)/src/*

libft:
	@make -sC $(LIBFT_DIR) --no-print-directory

mlx:
	@make -sC $(MLX_DIR) --no-print-directory

clean:
	@rm -rf $(OBJDIR)
	@make -sC $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@make -sC $(MLX_DIR) clean

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re libft run mlx
