# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:22:38 by graja             #+#    #+#              #
#    Updated: 2021/09/16 19:41:25 by graja            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol 
SRCS		= main.c
COMMON		= common/colors.c common/draw.c common/ccalc.c common/init.c \
		  common/hsv2rgb.c common/rgb2hsv.c common/hooks.c \
		  common/sets.c common/cmdline.c
FRACTALS	= fractals/mandel.c fractals/julia.c fractals/ship.c
CC		= gcc
LIBFT		= libft
FLGFT		= -Llibft -lft
FLGMLX		= -Lminilibx -lmlx -lXext -lX11 -lm
MLX		= minilibx

$(NAME)		:	$(SRCS) $(MLX) $(COMMON) $(LIBFT)
	make bonus -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(SRCS) $(COMMON) $(FRACTALS) $(FLGMLX) $(FLGFT) -o $(NAME)

all		:	$(NAME)

clean		:	$(LIBFT) $(MLX)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

bonus		:	all

fclean		:	$(LIBFT) $(MLX)
	rm -f $(NAME)
	rm -f $(MLX)/libmlx.a
	rm -f $(MLX)/libmlx_$(shell uname).a
	make fclean -C $(LIBFT)
