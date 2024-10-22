# Nombre de la librería
NAME = libft.a

# Compilador y flags
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror

# Directorio de fuentes
SRC_DIR = src

# Archivos fuente en el orden especificado
SOURCE_FILES =  ft_atoi.c \
				ft_itoa.c \
				ft_bzero.c \
				ft_split.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strlen.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_strlcat.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putchar_fd.c \

# Archivos bonus en el orden especificado
BONUS_FILES =	ft_lstnew_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \

# Directorio de archivos objeto
OBJDIR = libft_objects
# Archivos objeto generados a partir de los archivos fuente
OBJS = $(addprefix $(OBJDIR)/, $(SOURCE_FILES:.c=.o))
BONUS_OBJS = $(addprefix $(OBJDIR)/, $(BONUS_FILES:.c=.o))

# Reglas
all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	@ar rcs $@ $^

bonus: $(OBJDIR) $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
