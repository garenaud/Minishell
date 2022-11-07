# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:45:01 by grenaud-          #+#    #+#              #
#    Updated: 2022/11/07 15:11:10 by jsollett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

HEADER = 	minishell.h

CC = 		gcc
FLAGS = 	-g -Wall -Wextra -Werror
LDFLAGS=	 -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
CPPFLAGS=	 -I /Users/$(USER)/.brew/opt/readline/include 
DANGER = 	$(FLAGS) #-fsanitize=address
AR = 		ar -rcs
RM = 		@rm -rf

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"q
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

CFILES = 	Parser/list_utils_int.c \
			Parser/list_utils_int2.c \
			Parser/list_utils1.c \
			Parser/list_utils2.c \
			Parser/utils.c \
			Parser/parser.c \
			Parser/readline_util.c \
			minishell.c 


OBJECTS = $(CFILES:.c=.o)

#$(NAME): $(OBJECTS)
#		@echo "\n"
#		@echo $(B)"Compiling minishell..." $(X)
#		@$(CC) $(FLAGS) -o $(NAME)
#		@echo $(G)"Done !" $(X)

$(NAME): 	$(OBJECTS)
			@echo $(B)"Compiling minishell..." $(X)
			$(CC) $(FLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
			@echo $(G)"Done !" $(X)

all: 		$(NAME)

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