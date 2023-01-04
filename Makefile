# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:45:01 by grenaud-          #+#    #+#              #
#    Updated: 2023/01/04 14:10:53 by jsollett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

HEADER = 	minishell.h

CC = 		gcc
FLAGS = 	-g -Wall -Wextra -Werror
LDFLAGS=	 -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
CPPFLAGS=	 -I /Users/$(USER)/.brew/opt/readline/include
DANGER = 	 -fsanitize=address
AR = 		ar -rcs
RM = 		@rm -rf

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CFILES = 	Parser/list_utils_int.c \
			Parser/list_utils_int2.c \
			Parser/list_utils1.c \
			Parser/list_utils2.c \
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
			Parser/path.c \
			Parser/parser_util.c \
			Parser/memory_cleaning.c \
			Parser/token.c \
			minishell.c


OBJECTS = $(CFILES:.c=.o)

$(NAME): 	$(OBJECTS)
			@echo $(B)"Compiling minishell..." $(X)
			$(CC) $(FLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
			@echo $(G)"Done !" $(X)

all: 		$(NAME)

danger:		$(OBJECTS)
			@echo $(Y)"Compiling minishell with sanitize" $(X)
			$(CC) $(FLAGS) $(DANGER) $(OBJECTS) $(LDFLAGS) -o minishellSanit
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
	$(CC) $(CPPFLAGS) $(FLAGS) -c $^ -o $@

norm:
	@echo $(G)[--NORMINETTE SUCCES %100 CLEAN CODE...]$(G)
	norminette $(shell find ./Parser/ -name "*.c")


re: fclean all

.PHONY: re norm fclean clean all
