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

void print_struct(t_fract *fractol)
{

}

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

	return (0);
}

void	ft_error(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	exit(0);
}

void	init_struct(t_fract *fractol)
{
	fractol->mlx_ptr = NULL;
	fractol->win_ptr = NULL;
	fractol->img_ptr = NULL;
	fractol->image = NULL;
	fractol->bits_per_pixel = 0;
}

void	check_fractals(char *name)
{
	if (ft_strcmp(name, "mandelbrot") == 0)
	{
		ft_putstr("Rum Mandelbrot\n");
	}
	else
	{
		system("leaks fractol");
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	t_fract *fractol;

	if (argc != 2)
		ft_error("Incorrect num of parameters");
	check_fractals(argv[1]);
	fractol = (t_fract*)malloc(sizeof(t_fract));
	init_struct(fractol);
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, WIDTH, HEIGHT);
	fractol->image = (int *)mlx_get_data_addr(fractol->img_ptr,
		&fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	mandelbrot(fractol);
	mlx_hook(fractol->win_ptr, 2, 5, choose_key, fractol);
	mlx_hook(fractol->win_ptr, 17, 1L << 17, x_exit, 0);
	mlx_loop(fractol->mlx_ptr);

	return (0);
}
