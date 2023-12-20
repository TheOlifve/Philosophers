# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/11/22 15:52:22 by hrahovha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BUILD = build

CC = cc

SRC = 	src/main.c\
		src/load.c\
		src/utils.c\
		src/philo.c

OBJ = $(patsubst %.c, %.o, $(SRC))

MINI = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=thread

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)/src
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

all: $(NAME)

$(NAME) : $(MINI)
	$(CC) $(CFLAGS) $(MINI) $(INC) -o $(NAME)

fclean: clean
	rm -rf $(NAME) $(BUILD)
	
clean:
	rm -rf $(OBJ)


re: fclean all

.PHONY: all clean fclean re philo