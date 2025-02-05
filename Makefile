# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 11:07:00 by pibouill          #+#    #+#              #
#    Updated: 2025/02/05 15:43:23 by pibouill         ###   ########.fr        #
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
# LDFLAGS			:=	-lreadline -lncurses  
# Thats the path to the readline library on OSX
# will remove later
READINC			:= -I /opt/homebrew/opt/readline/include
LDFLAGS			:=	-lreadline -lncurses -L /opt/homebrew/opt/readline/lib
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
					builtins_utils\
					cd_builtin\
					cmd_exe\
					cmd_to_path\
					cmd_to_path_utils\
					cmds\
					cmds_utils\
					envp\
					exe_utils\
					export_builtin\
					heredoc\
					signals\
					lst_utils\
					main\
					parsing\
					parsing_utils\
					parsing_utils_2\
					parsing_utils_3\
					unset_builtin\
					utils\
					print_stuff\
					free_utils\
					update_env\
					add_cmd_arg\
					execute_commands\
					token_utils\
					cmd_exe_utils\
					get_cmd

SRC			:= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

################################################################################
## RULES

all: $(NAME) 

$(NAME): $(OBJ)
	+@make -C libft --no-print-directory
	+@$(CC) -o $(NAME) $(OBJ) -L $(LIBFT_DIR) -l $(LIBFT_CUT) $(LDFLAGS)
	+@echo ""
	+@echo "$(PREFIX)$(GREEN)[$(NAME) compiled]$(END_COLOR)"
	+@echo ""


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	+@$(CC) -c $(CFLAGS) $(INC_DIR) $(LIBFT_INC) $(READINC) $< -o $@
	+@echo "$(PREFIX)Compiling... $(GREEN)$(notdir $<) $(END_COLOR)"

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

val:
	@make
	@rm -rf leaks.log
	@valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=no_readline.supp --show-leak-kinds=all --log-file="leaks.log" ./minishell

test:
	@make re && cd minishell_tester && ./tester && cd ..

################################################################################
## PHONY

.PHONY: all clean fclean re test
