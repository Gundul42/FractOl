/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:07:05 by graja             #+#    #+#             */
/*   Updated: 2021/09/16 18:40:03 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	ft_reset_mandelbrot(t_data *data)
{
	data->type = 1;
	data->maxreal = 1.0;
	data->minreal = -2.0;
	data->maximg = 1.0;
	data->minimg = -1.0;
	data->zoom = 1.0;
	data->movex = 0;
	data->movey = 0;
	ft_draw_fractal(data);
}

void	ft_goto_julia(t_data *data, int x, int y)
{
	data->type = 2;
	data->maxreal = 1.8;
	data->minreal = -1.8;
	data->maximg = 1.2;
	data->minimg = -1.2;
	data->juliaimg = ft_getimg(y, data);
	data->juliareal = ft_getreal(x, data);
	data->zoom = 0.6;
	data->movex = 0;
	data->movey = 0;
	ft_draw_fractal(data);
}

void	ft_init_window(t_data *data, int x, int y, int i)
{
	data->x = x;
	data->y = y;
	data->i = i;
	data->maxreal = 1.0;
	data->minreal = -2.0;
	data->maximg = 1.0;
	data->minimg = -1.0;
	data->zoom = 1.0;
	data->movex = 0;
	data->movey = 0;
	data->juliareal = -1;
	data->juliaimg = 0.5;
}

t_data	*ft_blank(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->type = 0;
	data->x = 0;
	data->y = 0;
	data->i = 0;
	data->minreal = .0;
	data->maxreal = .0;
	data->minimg = .0;
	data->maximg = .0;
	data->juliareal = .0;
	data->juliaimg = .0;
	data->zoom = .0;
	data->movex = .0;
	data->movey = .0;
	data->breakpts = NULL;
	data->palette = NULL;
	return (data);
}
