# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:45:01 by grenaud-          #+#    #+#              #
#    Updated: 2023/01/16 17:24:10 by grenaud-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

HEADER = 	minishell.h

CC = 		gcc
FLAGS = 	-g -Wall -Wextra -Werror
TESTFLAGS = -O1 -ggdb3
LDFLAGS=	 -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
CPPFLAGS=	 -I /Users/$(USER)/.brew/opt/readline/include
DANGER = 	 -fsanitize=address -fno-omit-frame-pointer
AR = 		ar -rcs
RM = 		@rm -rf

Y = "\033[33m"
R = "\033[31m"
G = \033[32m
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"
REVR = \033[7m
BOLD = "\033[1m"

CFILES = 	Parser/list_utils_int.c \
			Parser/list_utils_int2.c \
			Parser/list_utils1.c \
			Parser/list_utils2.c \
			Parser/list_utils3.c \
			Parser/utils.c \
			Parser/utils1.c \
			Parser/parser.c \
			Parser/parser_1.c \
			Parser/parser_2.c \
			Parser/readline_util.c \
			Parser/parsing_init.c \
			Parser/parsing_init_1.c \
			Parser/parsing_init_2.c \
			Parser/test.c \
			Parser/dico.c \
			Parser/dico_1.c \
			Parser/dico_2.c \
			Parser/dico_3.c \
			Parser/dico_4.c \
			Parser/path.c \
			Parser/parser_util.c \
			Parser/memory_cleaning.c \
			Parser/token.c \
			Parser/token1.c \
			Parser/token2.c \
			Parser/token_test.c \
			Exec/redir_utils.c \
			Exec/init.c \
			Exec/exe.c \
			Exec/check_pipe_utils.c \
			Exec/list_utils_exe.c \
			Exec/utils_2.c \
			Exec/pipe.c \
			Exec/redirection.c \
			Builtin/built_utils.c \
			Builtin/builtins.c \
			Builtin/echo.c \
			Builtin/cd.c \
			Builtin/export.c \
			Builtin/env.c \
			Builtin/unset.c \
			signal.c \
			start_banner.c \
			minishell.c


OBJECTS = 	$(CFILES:.c=.o)

LIBFT = libft/

$(NAME): 	start $(OBJECTS)
			@echo $(BOLD) "SUCCESSFUL COMPILATION" $(X)
			@$(CC) $(FLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
			@tput setaf 3; cat includes/art; tput setaf default
			@echo $(G)"Done !" $(X)

all: 		$(NAME)

start:
			@tput setaf 2; cat includes/artCompiling; tput setaf default

danger:		$(OBJECTS)
			@echo $(Y)"\n Compiling minishell with -fsanitize=address \n" $(X)
			@$(CC) $(FLAGS) $(DANGER) $(OBJECTS) $(LDFLAGS) -o minishellSanit
			@tput setaf 3; cat includes/danger; tput setaf default

libft:
			@ $(MAKE) bonus -C $(LIBFT)

clean:
	$(RM) ./Parser/*.o
	$(RM) ./*.o
	$(RM) ./*.d
	@echo $(R)Removed [./Parser/*.o]$(X)
	@echo $(R)Removed [./*.o]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)

fclean:
	@tput setaf 3; cat includes/trash; tput setaf default
	$(RM) ./minishell
	@echo $(B)Removed [TEMPORARY FILES]$(X)
	$(RM) ./parser/*.o
	@echo $(R)Removed [./Parser/*.o]$(X)
	$(RM) ./Exec/*.o
	@echo $(R)Removed [./Exec/*.o]$(X)
	$(RM) ./Builtin/*.o
	@echo $(R)Removed [./Builtin/*.o]$(X)
	$(RM) ./a.out.dSYM
	$(RM) ./*.o
	$(RM) ./minishellSanit
	$(RM) ./Exec/*.o
	@echo $(R)Removed [./Exec/*.o]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)

%.o: %.c
	@$(CC) $(CPPFLAGS) $(FLAGS) -c $^ -o $@
	@printf "$(G) $(REVR)  " $(X)

norm:
	@echo $(G)[--NORMINETTE SUCCES %100 CLEAN CODE...]$(G)
	norminette $(shell find ./Parser/ -name "*.c")


re: fclean all

.PHONY: re norm fclean clean all start
