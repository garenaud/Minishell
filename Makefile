# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 17:45:01 by grenaud-          #+#    #+#              #
#    Updated: 2022/11/07 11:27:04 by grenaud-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = 		gcc
FLAGS = 	-Wall -Wextra -Werror -g3 
DANGER = 	$(FLAGS) #-fsanitize=address
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
			Parser/parser.c \
			#minishell.c

NAME =		minishell.c

HEADER = 	minishell.h

OBJECTS = $(CFILES:.c=.o)

#$(NAME): $(OBJECTS)
#		@echo "\n"
#		@echo $(B)"Compiling minishell..." $(X)
#		@$(CC) $(FLAGS) -o $(NAME)
#		@echo $(G)"Done !" $(X)

$(NAME): 	$(OBJECTS)
			@echo $(B)"Compiling minishell..." $(X)
			$(CC) $(FLAGS) $(OBJECTS) $(NAME)
			@mv a.out minishell
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
	$(CC) $(FLAGS) -c -o $@ $<

norm:
	@echo $(G)[--NORMINETTE SUCCES %100 CLEAN CODE...]$(G)
	norminette $(shell find ./Parser/ -name "*.c")


re: fclean all

.PHONY: re norm fclean clean all 