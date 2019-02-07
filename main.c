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

#include <stdio.h>

#include "fractol.h"

int				x_exit(void *param)
{
	param = NULL;
	system("leaks fractol");
	exit(0);
	return (0);
}

int				choose_key(int key, void *param)
{
	t_fract *fractol;

	fractol = (t_fract*)param;
	if (key == 53)
		x_exit(param);
	else if (key == PLUS_ITER)
		fractol->max_iterations += 5;
	else if (key == MINUS_ITER && fractol->max_iterations > 0)
		fractol->max_iterations -= 5;

	// set_threads(fractol);
	choose_fractal(fractol);

	return (0);
}

int			move_mouse(int key, int x, int y, t_fract *fractol)
{
	// printf("key = %d | x = %d | y = %d\n", key, x, y);
	double coeff;

	coeff = 1;
	if (key == MOUSE_PLUS)
	{
		coeff = 9.0 / 10;
		printf("coeff = %f\n", coeff);
	}
	else if (key == MOUSE_MINUS)
	{
		coeff = 10.0 / 9;
		printf("coeff = %f\n", coeff);
	}

	fractol->delta_re *= coeff;
	fractol->delta_im *= coeff;

	// fractol->min_re = fractol->min_re + ((double)x / WIDTH) * fractol->delta_re / coeff * (1 - coeff);
	// fractol->min_im = fractol->min_im - ((double)(HEIGHT - y) / HEIGHT) * fractol->delta_im / coeff * (1 - coeff);

	fractol->min_re = fractol->min_re + ((double)x / WIDTH) * fractol->delta_re / coeff * (1 - coeff);
	fractol->min_im = fractol->min_im - ((double)(HEIGHT - y) / HEIGHT) * fractol->delta_im / coeff * (1 - coeff);

	printf("fractol->min_re = %f\n", fractol->min_re);
	printf("fractol->min_im = %f\n", fractol->min_im);
	// set_threads(fractol);
	choose_fractal(fractol);
	return (0);
}

void	ft_error(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	exit(0);
}

void	usage()
{
	ft_putstr("Usage: ./fractol [fractal]\n");
	ft_putstr("[fractal] can be equal:\n- mandelbrot\n");
	exit(0);
}

void	init_struct(t_fract *fractol)
{
	fractol->mlx_ptr = NULL;
	fractol->win_ptr = NULL;
	fractol->img_ptr = NULL;
	fractol->image = NULL;
	fractol->bits_per_pixel = 0;
	fractol->max_iterations = 50;

	fractol->type_fractal = 0;
	//check vars
	fractol->delta_re = 3.0;
	fractol->delta_im = 2.4;

	fractol->min_re = -2.0;
	fractol->max_re = 1.0;

	// fractol->min_im = -1.2;
	// fractol->max_im = 1.2;

	fractol->min_im = 1.2;
	fractol->max_im = -1.2;

	// fractol->zoom = 200;
}

void	check_fractals(t_fract *fractol, char *name)
{
	if (ft_strcmp(name, "mandelbrot") == 0)
	{
		ft_putstr("Run Mandelbrot\n");
		fractol->type_fractal = MANDELBROT;
	}
	else if (ft_strcmp(name, "julia") == 0)
	{
		ft_putstr("Run Julia\n");
		fractol->type_fractal = JULIA;
	}
	else
	{
		// system("leaks fractol");
		usage();
	}
}

int main(int argc, char *argv[])
{
	t_fract *fractol;

	if (argc != 2)
		usage();
	fractol = (t_fract*)malloc(sizeof(t_fract));
	init_struct(fractol);
	check_fractals(fractol, argv[1]);
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	fractol->image = (int *)mlx_get_data_addr(fractol->img_ptr,
		&fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	// set_threads(fractol);
	choose_fractal(fractol);
	mlx_hook(fractol->win_ptr, 2, 5, choose_key, fractol);
	mlx_hook(fractol->win_ptr, 4, 0, move_mouse, fractol);
	mlx_hook(fractol->win_ptr, 17, 1L << 17, x_exit, 0);
	mlx_loop(fractol->mlx_ptr);

	return (0);
}
