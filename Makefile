# =============================================================================
#                                FDF - Makefile
# =============================================================================

# ======================== Compiler and Flags ================================
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
IFLAGS  := -I./headers
LDFLAGS := -L./helpers/libft -L./helpers/minilibx-linux/minilibx-linux -lft -lmlx -lX11 -lXext -lm

# ======================== Project Name ======================================
NAME    := fdf

# ======================== Directories =======================================
SRC_DIR     := src
HEADERS_DIR := headers
HELPERS_DIR := helpers

LIBFT_DIR   := $(HELPERS_DIR)/libft
GNL_DIR     := $(HELPERS_DIR)/get_next_line
MLX_DIR     := $(HELPERS_DIR)/minilibx-linux/minilibx-linux

# ======================== Source Files (hardcoded) ==========================
SRC := \
	src/key_handling.c \
	src/main.c \
	src/mouse.c \
	src/paral.c \
	src/parse/counts.c \
	src/parse/frees.c \
	src/parse/ft_atoi_base.c \
	src/parse/parsing.c \
	src/drawing/calculations.c \
	src/drawing/projection.c

OBJ := $(SRC:.c=.o)

# ======================== GNL (get_next_line) ===============================
GNL_SRC := \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

GNL_OBJ := $(GNL_SRC:.c=.o)

# ======================== Libraries =========================================
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_DIR)/libmlx.a

# ======================== Build Rules =======================================

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJ) $(LIBFT) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(GNL_OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@echo "Building MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(GNL_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

bonus: all

re: fclean all

# ======================== PHONY RULES =======================================
.PHONY: all clean fclean re bonus

