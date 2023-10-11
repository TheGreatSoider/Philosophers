# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 16:46:59 by cocheong          #+#    #+#              #
#    Updated: 2023/10/02 16:46:59 by cocheong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

SRCS = actions.c \
		avcheck.c \
		init.c \
		main.c \
		threads.c \
		utils.c

OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))


HEADER_PATH = .

OBJS_DIR = objs/

all: $(NAME)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@echo Compiling [$<]
	@$(CC) $(CFLAGS) -c -I$(HEADER_PATH) $< -o $@ 


$(NAME): $(OBJECTS_PREFIXED)
	@$(CC) $(CFLAGS) $(OBJECTS_PREFIXED) -o $(NAME)
	@echo [$(NAME)]

clean:
	@rm -f $(OBJECTS)
	@echo Removed [$(OBJECTS)]

fclean: clean
	@rm -f $(NAME)
	@echo Removed [$(NAME)]

re: fclean all

.PHONY: all clean fclean re norm