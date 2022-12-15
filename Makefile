# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:45:01 by grenaud-          #+#    #+#              #
#    Updated: 2022/12/15 16:05:17 by grenaud-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

HEADER = 	minishell.h

CC = 		gcc
FLAGS = 	-g -ggdb3 -Wall -Wextra -Werror
LDFLAGS=	 -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
CPPFLAGS=	 -I /Users/$(USER)/.brew/opt/readline/include 
DANGER = 	 -fsanitize=address
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
			Parser/utils.c \
			Parser/parser.c \
			Parser/readline_util.c \
			Parser/parsing_init.c \
			Parser/test.c \
			Parser/dico.c \
			Parser/path.c \
			Exec/init.c \
			minishell.c


OBJECTS = 	$(CFILES:.c=.o)

$(NAME): 	start $(OBJECTS)                                      
			@echo $(BOLD) "SUCCESSFUL COMPILATION" $(X)
			@$(CC) $(FLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
			@tput setaf 3; cat includes/art; tput setaf default
			@echo $(G)"Done !" $(X)

all: 		$(NAME)

start:		
			@tput setaf 2; cat includes/artCompiling; tput setaf default

danger:		$(OBJECTS)
			@echo $(Y)"Compiling minishell with sanitize" $(X)
			@$(CC) $(FLAGS) $(DANGER) $(OBJECTS) $(LDFLAGS) -o minishellSanit
			@echo $(Y)"Done !" $(X)

clean:
	$(RM) ./Parser/*.o
	$(RM) ./*.o
	$(RM) ./*.d
	@echo $(R)Removed [./Parser/*.o]$(X)
	@echo $(R)Removed [./*.o]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)
	@echo $(R)Removed [REMOVED FINISH]$(X)

fclean:
	$(RM) ./minishell
	$(RM) ./parser/*.o
	$(RM) ./a.out.dSYM
	$(RM) ./*.o
	$(RM) ./minishellSanit
	@echo $(B)Removed [TEMPORARY FILES]$(X)
	@echo $(R)Removed [./Parser/*.o]$(X)
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