# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:22:38 by graja             #+#    #+#              #
#    Updated: 2021/09/12 13:19:39 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/ccalc.c common/init.c \
		  common/hsv2rgb.c common/rgb2hsv.c
FRACTALS	= fractals/mandel.c fractals/julia.c fractals/ship.c
CC		= gcc
LIBFT		= libft
FLGFT		= -Llibft -lft
FLGMLX		= -Lminilibx -lmlx_Linux -lXext -lX11 -lm
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	$(CC) $(SRCS) $(COMMON) $(FRACTALS) $(FLGMLX) $(FLGFT) -o $(NAME)

all		:	$(NAME)
