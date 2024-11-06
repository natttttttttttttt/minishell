# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: visaienk <visaienk@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 11:40:58 by pibouill          #+#    #+#              #
#    Updated: 2024/11/06 11:18:02 by pibouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	cc
RM			:=	rm -rf
CFLAGS		:=	-Wall -Werror -Wextra -g
SRC_DIR		:=	src
INC_DIR		:=	-I ./inc/
LIB_DIR		:=	lib
LIBFT_DIR	:=	libft
LIBFT_INC	:=	-I ./libft/inc/
BIN_DIR		:=	bin
LIBFT_CUT	:= $(shell echo $(LIBFT_DIR) | cut -c 4-)

################################################################################
## COLORS
UNAME		:= $(shell uname)

RED				:=	[38;5;9m
GREEN			:=	[38;5;10m
BLUE			:= 	[38;5;14m
YELLOW			:=	[38;5;226m
RESET			:=	[38;5;7m
PREFIX			:=	[$(YELLOW)$(NAME)$(RESET)]\t\t\t\t

#ifeq ($(UNAME), Linux)
	#RED			:= \e[38;5;196m
	#ORANGE		:= \e[38;5;208m
	#GREEN		:= \033[0;92m
	#YELLOW      := \033[0;93m
	#BLUE        := \033[0;94m
	#END_COLOR	:= \033[0;39m
#endif
#ifeq ($(UNAME), Darwin)
	#GREEN		:= \033[0;92m
	#YELLOW      := \033[0;93m
	#BLUE        := \033[0;94m
	#RED         := \033[0;91m
	#END_COLOR   := \033[0m
#endif

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
				   free_utils_and_strjoin

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

################################################################################
## PHONY

.PHONY: all clean fclean re
