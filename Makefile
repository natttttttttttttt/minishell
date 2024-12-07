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
LDFLAGS			:=	-lreadline -lncurses  
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
					cmds\
					cmds_utils\
					envp\
					exe_utils\
					execute_cmd\
					export_builtin\
					heredoc\
					signals\
					lst_utils\
					main\
					parsing\
					parsing_utils\
					unset_builtin\
					utils\
					print_stuff\
					vars\
					vars_utils

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

val:
	@make
	@valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=suppress --show-leak-kinds=all --log-file="leaks" ./minishell


################################################################################
## PHONY

.PHONY: all clean fclean re
