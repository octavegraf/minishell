# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 09:37:05 by ljudd             #+#    #+#              #
#    Updated: 2025/10/06 14:20:28 by ljudd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
#DEBUG			= -g3
CFLAGS			= -Wall -Wextra -Werror -MMD -MP $(DEBUG)
NAME			= minishell
INCLUDES		= -Ilibft -Iincludes

# Sources
SRC_FOLDER		= src/
BUILTIN_FOLDER	= $(SRC_FOLDER)builtin/
EXEC_FOLDER		= $(SRC_FOLDER)exec/
PARSING_FOLDER	= $(SRC_FOLDER)parsing/
BUILTIN			= builtin.c cd.c echo.c env.c exit.c export.c \
					export_2.c pwd.c unset.c
EXEC			= args.c env_to_array.c exec2.c exec.c free.c \
					get_env2.c get_env.c pipes.c redirs.c redirs_heredoc.c \
					redirs_utils.c signals.c signals_heredoc.c \
					wrapper.c
PARSING			= expander_2.c expander.c merge_adjacent.c news.c parsing.c \
					pretoken.c pretoken_subfunc.c tokenization.c \
					token_to_cmd.c utils.c
SOURCES			= $(addprefix $(BUILTIN_FOLDER), $(BUILTIN)) $(addprefix $(EXEC_FOLDER), $(EXEC)) \
					$(addprefix $(PARSING_FOLDER), $(PARSING))

# Objects
OBJ_PATH		= obj/
OBJ				= $(SOURCES:.c=.o)
OBJECTS			= $(addprefix $(OBJ_PATH), $(OBJ))
DEP				= $(SOURCES:.c=.d)
DEPS			= $(addprefix $(OBJ_PATH), $(DEP))

# libft
LIBFT			= libft.a
LIBFT_FLAGS		= -Llibft -lft
LIBFT_DIR		= libft/

# Colors for display
RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(BLUE)%s$(RESET): $(YELLOW)Building $(NAME)...$(RESET)\n" $(NAME)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAGS) -o $(NAME) -lreadline
	@printf "$(BLUE)%s$(RESET): $(GREEN)Successfully built $(NAME)$(RESET)\n" $(NAME)

$(OBJ_PATH)%.o: %.c | $(OBJ_PATH)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIBFT):
	@make -C $(LIBFT_DIR) all --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Cleaning object files...$(RESET)\n" $(NAME)
	@rm -rf obj
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Full clean...$(RESET)\n" $(NAME)
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
.DELETE_ON_ERROR: