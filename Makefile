NAME = minirt

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -lmlx -lX11 -lXext -lXrender -pthread# -Wpedantic -Wshadow -Wformat -Wnull-dereference -Wconversion -Wstrict-overflow -Wsign-conversion -Wimplicit-fallthrough=5 -Wdouble-promotion -Wvla -Wformat-security -Wcast-align=strict -Wredundant-decls -Wlogical-op -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Winit-self -Wuninitialized -Wbad-function-cast -Wmissing-field-initializers

TIDY_FLAGS = --checks="*,-clang-analyzer-alpha.*,-google-readability-braces-around-statements,-hicpp-braces-around-statements,-readability-braces-around-statements,-modernize-*,-cppcoreguidelines-*,-clang-analyzer-cplusplus.*"

# analyze:
# 	@if [ -z "$(FILE)" ]; then \
# 		echo "Por favor, especifica el archivo que quieres analizar con FILE=archivo.c"; \
# 	else \
# 		clang-tidy $(FILE) $(TIDY_FLAGS) -- -Iinclude -Wall -Wextra -Werror; \
# 	fi

SRC_DIR = src
OBJDIR = $(NAME)_objects

INCLUDE_SRC =	file.h \
				main.h \
				utils.h \
				hooks.h \
				render.h \
				struct.h \
				colors.h \
				include.h \
				math_struct.h \
				objects_struct.h \

INCLUDES = $(addprefix include/, $(INCLUDE_SRC))

GNL_SRC =		get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \

MAIN_SRC =      src/main/ft_main.c \
                src/main/ft_window.c \
                src/main/ft_initialize.c \

RENDER_SRC =    src/render/ft_maths.c \
				src/render/ft_dotv3.c \
				src/render/ft_render.c \
				src/render/ft_cy_formula.c \

SRCS = 	$(GNL_SRC) \
		$(MAIN_SRC) \
		$(RENDER_SRC) \

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm

all: $(OBJDIR) libft mlx $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_FLAGS)

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

.PHONY: all clean fclean re libft mlx
