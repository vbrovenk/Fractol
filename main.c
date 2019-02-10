/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:57:33 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/01/27 16:57:35 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	void	usage(void)
{
	ft_putstr("Usage: ./fractol [fractal]\n");
	ft_putstr("[fractal] can be equal:\n> mandelbrot\n> julia\n");
	ft_putstr("> burningship\n> tricorn\n");
	ft_putstr("> julia5\n> hall\n> leaf\n> last\n");
	exit(0);
}

static	void	check_fractals(t_fract *fractol, char *name)
{
	if (ft_strcmp(name, "mandelbrot") == 0)
		fractol->type_fractal = MANDELBROT;
	else if (ft_strcmp(name, "julia") == 0)
		fractol->type_fractal = JULIA;
	else if (ft_strcmp(name, "burningship") == 0)
		fractol->type_fractal = SHIP;
	else if (ft_strcmp(name, "tricorn") == 0)
		fractol->type_fractal = TRICORN;
	else if (ft_strcmp(name, "julia5") == 0)
		fractol->type_fractal = JULIA_5;
	else if (ft_strcmp(name, "hall") == 0)
		fractol->type_fractal = HALL;
	else if (ft_strcmp(name, "leaf") == 0)
		fractol->type_fractal = LEAF;
	else if (ft_strcmp(name, "last") == 0)
		fractol->type_fractal = LAST;
	else
		usage();
}

void			reset_params(t_fract *fractol)
{
	fractol->max_iterations = 50;
	fractol->min_re = -2.0;
	fractol->min_im = -2.0;
	fractol->delta = 4.0;
}

static	void	init_struct(t_fract *fractol)
{
	fractol->mlx_ptr = NULL;
	fractol->win_ptr = NULL;
	fractol->img_ptr = NULL;
	fractol->image = NULL;
	fractol->bits_per_pixel = 0;
	fractol->max_iterations = 50;
	fractol->type_fractal = -1;
	fractol->min_re = -2.0;
	fractol->min_im = -2.0;
	fractol->delta = 4.0;
	fractol->space_on = -1;
	fractol->color = 0;
	fractol->mouse_x = 110;
	fractol->mouse_y = 344;
	fractol->help = -1;
}

int				main(int argc, char *argv[])
{
	t_fract *fractol;

	if (argc != 2)
		usage();
	fractol = (t_fract*)malloc(sizeof(t_fract));
	init_struct(fractol);
	check_fractals(fractol, argv[1]);
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WIDTH, HEIGHT,
																"FRACTOL");
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	fractol->image = (int *)mlx_get_data_addr(fractol->img_ptr,
		&fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	choose_fractal(fractol);
	mlx_hook(fractol->win_ptr, 2, 5, choose_key, fractol);
	mlx_hook(fractol->win_ptr, 4, 0, zoom_mouse, fractol);
	mlx_hook(fractol->win_ptr, 6, 0, move_mouse, fractol);
	mlx_hook(fractol->win_ptr, 17, 1L << 17, x_exit, 0);
	mlx_loop(fractol->mlx_ptr);
	return (0);
}
