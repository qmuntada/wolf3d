#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/07 16:04:22 by qmuntada          #+#    #+#              #
#    Updated: 2015/10/30 14:41:35 by qmuntada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CFLAGS = -Wall -Werror -Wextra
SRC = env.c error.c event.c fps.c line.c line2.c main.c mouse.c movement.c \
		pre_computed.c ray_cast.c ray_cast2.c render.c sprite.c sprite2.c \
		sprite3.c texture.c tools.c vector_tools.c weapon.c
OBJ = $(SRC:.c=.o)
mlx = minilibx_macos
lft = libft

all : $(NAME)

$(NAME) : $(ft) $(mlx)
	@echo "Creating MAC executable $@ ..."
	@make -C $(lft)
	@make -C $(mlx)
	@gcc $(FLAGS) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) -L $(lft) -lft -L $(mlx) -lmlx -framework OpenGl -framework AppKit

libft:
	@make -C libft fclean
	@make -C libft

clean :
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re : fclean all
