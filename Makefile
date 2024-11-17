# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: visaienk <visaienk@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 11:40:58 by pibouill          #+#    #+#              #
#    Updated: 2024/11/17 15:24:55 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell
CC				:=	cc
RM				:=	rm -rf
CFLAGS			:=	-Wall -Werror -Wextra -g
SRC_DIR			:=	src
INC_DIR			:=	-I ./inc/
LIB_DIR			:=	lib
LIBFT_DIR		:=	libft
LIBFT_INC		:=	-I ./libft/inc/
BIN_DIR			:=	bin
LIBFT_CUT		:= $(shell echo $(LIBFT_DIR) | cut -c 4-)

################################################################################
## COLORS
UNAME			:= $(shell uname)

RED				:=	[38;5;9m
GREEN			:=	[38;5;10m
BLUE			:= 	[38;5;14m
YELLOW			:=	[38;5;226m
RESET			:=	[38;5;7m
PREFIX			:=	[$(YELLOW)$(NAME)$(RESET)]\t\t\t\t
SUBMOD_PREFIX	:=	[$(BLUE)Submodules$(RESET)]\t\t\t\t

################################################################################
## SOURCES

SRC_FILES	:=		builtins\
					cmd_exe\
					cmds\
				   	envp\
				   	heredoc\
				   	lst_utils\
				   	main\
				   	parsing\
				   	utils_2\
				   	vars\
				   	vars_utils\
				   	lst_free_utils\
				   	free_utils_and_strjoin\
				   	envp_utils\
					cd\
					exit\
					export\
					add_cmd_arg\
					signals

SRC			:= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

################################################################################
## RULES

all: $(NAME) 

$(NAME): $(OBJ)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(NAME) $(OBJ) -L $(LIBFT_DIR) -l $(LIBFT_CUT) -lreadline
	+@echo ""
	+@echo "$(PREFIX)$(GREEN)[$(NAME) compiled]$(END_COLOR)"
	+@echo ""


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	+@$(CC) -c $(CFLAGS) $(INC_DIR) $(LIBFT_INC) $< -o $@
	+@echo "$(PREFIX)Compiling... $(BLUE)$(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	+@mkdir $(BIN_DIR)
	+@echo "$(PREFIX)Created $(BIN_DIR)/"

clean:
	 +@rm -rf $(BIN_DIR)
	 +@echo "$(PREFIX)$(NAME) object files cleaned"
	 +@make clean -C libft --no-print-directory

fclean: clean
	+@$(RM) bin $(NAME) libft/libft.a 
	+@echo "$(PREFIX)$(NAME) executable file cleaned"
	+@echo "$(PREFIX)$(NAME) bin/ cleaned"

re: fclean all
	+@echo "$(PREFIX)Cleaned all and rebuilt $(NAME) and $(LIBFT_DIR)"

minish: all
	+@ ./minishell
#submodules_init:
#    +@git submodule update --init --recursive
#    @echo "$(SUBMOD_PREFIX)Initialized and updated$(END_COLOR)"

val:
	@make
	@valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=suppress --show-leak-kinds=all --log-file="leaks" ./minishell


################################################################################
## PHONY

.PHONY: all clean fclean re
