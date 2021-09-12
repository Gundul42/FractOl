/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graja <graja@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:43:51 by graja             #+#    #+#             */
/*   Updated: 2021/09/12 15:44:30 by graja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/fractol.h"

int	the_end(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->palette);
	free(data->breakpts);
	free(data);
	exit (0);
	return (0);
}

int	key_hook(int code, t_data *data)
{
	printf("You pressed the key %d in window\n", code);
	if (code == 65307)
		the_end(data);
	return (code);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	static t_numbr	upper;
	static t_numbr	lower;
	static int	oldx;
	static int	oldy;
	double		xshift;
	double		yshift;

	printf("MOUSE = %d Button, %dx, %dy\n", button, x, y);
	if (button == 4)
	{
		ft_mmove(data, x, y, 0.3);
		data->zoom *= 1.1; 
		ft_draw_fractal(data);
	}
	if (button == 5)
	{
		ft_mmove(data, x, y, 0.3);
		data->zoom /= 1.1;
		if (data->zoom < 0.5)
			data->zoom = 0.6;
		ft_draw_fractal(data);
	}
	if (button == 8)
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
	if (button == 10)
	{
		data->maxreal = 1.8;
		data->minreal = -1.8;
		data->maximg = 1.2;
		data->minimg = -1.2;
		data->juliaimg = ft_getimg(y, data);
		data->juliareal = ft_getreal(x, data);
		data->zoom = 1.0;
		data->movex = 0;
		data->movey = 0;
		data->type = 2;
		ft_draw_fractal(data);
	}
	return (0);
}

int	mouse_move(int x,int y, void *p)
{
	double	re;
	double	im;
	t_data	*f;

	f = (t_data *)p;
	re = ft_getreal(x, f);
	im = ft_getimg(y, f);
	printf("TYPE= %d >>>Re= %2.12f  -  Im= %2.12f  -  Zo= %8.2f\n", f->type, re, im, f->zoom);
}

int	ft_get_cmdline(int argc, char **argv, t_data **ptr)
{
	t_data	*f;

	f = malloc(sizeof(t_data));
	if (!f || argc < 2)
		return (0);
	if (!ft_strncmp(argv[1], "mandel", ft_strlen(argv[1])))
		f->type = 1;
	else if (!ft_strncmp(argv[1], "julia", ft_strlen(argv[1])))
		f->type = 2;
	else if (!ft_strncmp(argv[1], "ship", ft_strlen(argv[1])))
		f->type = 3;
	else
		return (0);
	f->x = 1200;
	f->y = 800;
	f->i = 1000;
	f->maxreal = 1.0;
	f->minreal = -2.0;
	f->maximg = 1.0;
	f->minimg = -1.0;
	f->zoom = 1.0;
	f->movex = 0;
	f->movey = 0;
	f->juliareal = -1;
	f->juliaimg = 0.5;
	if (argc > 2) 
		f->x = ft_atoi(argv[2]);
	if (argc > 3)
		f->y = ft_atoi(argv[3]);
	if (argc > 4)
		f->i = ft_atoi(argv[4]);
	*ptr = f;
	return (1);
}

int	ft_loop_hook(t_data *img)
{
	mlx_do_sync(img->mlx);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	*img;

	if (!ft_get_cmdline(argc, argv, &img))
		return (1);
	img->mlx = mlx_init();
	if (!img->mlx)
		return (1);
	img->breakpts = ft_init_colors();
	img->palette = ft_init_palette(img);
	img->win = mlx_new_window(img->mlx, img->x, img->y, "Gundul's Mandel (beta v1.0)");
	img->img = mlx_new_image(img->mlx, img->x, img->y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	ft_draw_fractal(img);
	mlx_key_hook(img->win, key_hook, img);
	mlx_mouse_hook(img->win, mouse_hook, img);
	mlx_hook(img->win, 6, (1L << 6), mouse_move, img);
	mlx_loop_hook(img->mlx, ft_loop_hook, img);
	mlx_loop(img->mlx);
	return (0);
}
