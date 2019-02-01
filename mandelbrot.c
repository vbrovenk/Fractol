/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:58:09 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/01/31 14:58:10 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

// void	init_vars(t_vars *vars)
// {
// 	vars->min_re = -2.0;
// 	vars->max_re = 1.0;
// 	vars->min_im = -1.2;
// 	vars->max_im = 1.2;

// 	vars->z_re = 0;
// 	vars->z_im = 0;
// 	vars->c_im = 0;
// 	vars->c_re = 0;
// 	vars->zoom = 200;

// 	vars->re_factor = (vars->max_re - vars->min_re) / (WIDTH - 1);
// 	vars->im_factor = (vars->max_im - vars->min_im) / (HEIGHT - 1);
// }

// void	iters(t_fract *fractol, t_vars *vars, int x, int y)
// {
// 	int		n;
// 	double	tmp;

// 	n = -1;
// 	while (++n < fractol->iterations)
// 	{
// 		tmp = vars->z_re;
// 		vars->z_re = vars->z_re * vars->z_re - vars->z_im * vars->z_im + vars->c_re;
// 		vars->z_im = 2 * vars->z_im * tmp + vars->c_im;
// 		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
// 			break;
// 	}
// 	if (n == fractol->iterations)
// 		fractol->image[x + y * WIDTH] = 0x000000;
// 	else
// 	{
// 		fractol->image[x + y * WIDTH] = 0xFFFFFF;
// 	}
// }

// void	mandelbrot(t_fract *fractol)
// {
// 	t_vars	vars;
// 	int		y;
// 	int		x;
// 	double tmp = 0;


// 	init_vars(&vars);
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < HEIGHT)
// 		{
// 			vars.z_re = 0;
// 			vars.z_im = 0;

// 			// ============ Variant 1 ============
// 			// vars.c_re = x / vars.zoom + vars.min_re;
// 			// vars.c_im = y / vars.zoom + vars.min_im;

// 			// ============ Variant 2 ============
// 			vars.c_re = vars.min_re + x * vars.re_factor;
// 			vars.c_im = vars.max_im - y * vars.im_factor;

// 			iters(fractol, &vars, x, y);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0,0);
// }


void	init_vars(t_vars *vars)
{
	vars->min_re = -2.0;
	vars->max_re = 1.0;
	vars->min_im = -1.2;
	vars->max_im = 1.2;

	vars->z_re = 0;
	vars->z_im = 0;
	vars->c_im = 0;
	vars->c_re = 0;
	vars->zoom = 200;

	vars->re_factor = (vars->max_re - vars->min_re) / (WIDTH - 1);
	vars->im_factor = (vars->max_im - vars->min_im) / (HEIGHT - 1);
}

void	iters(t_fract *fractol, t_vars *vars, int x, int y)
{
	int		n;
	double	tmp;

	n = -1;
	while (++n < fractol->iterations)
	{
		tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re - vars->z_im * vars->z_im + vars->c_re;
		vars->z_im = 2 * vars->z_im * tmp + vars->c_im;
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break;
	}
	if (n == fractol->iterations)
	{
		// mlx_pixel_put(fractol->mlx_ptr, fractol->win_ptr, x, y, 0x000000);
		fractol->image[x + y * WIDTH] = 0x000000;
	}
	else
	{
		// mlx_pixel_put(fractol->mlx_ptr, fractol->win_ptr, x, y, 0xFFFFFF);
		fractol->image[x + y * WIDTH] = 0xFFFFFF;
	}
}

void	mandelbrot(t_fract *fractol)
{
	t_vars	vars;
	int		y;
	int		x;
	double tmp = 0;


	init_vars(&vars);
	y = fractol->start;
	while (y < HEIGHT / 4 + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;

			// ============ Variant 1 ============
			// vars.c_re = x / vars.zoom + vars.min_re;
			// vars.c_im = y / vars.zoom + vars.min_im;

			// ============ Variant 2 ============
			vars.c_re = vars.min_re + x * vars.re_factor;
			vars.c_im = vars.max_im - y * vars.im_factor;

			iters(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}


void	set_threads(t_fract *fractol)
{
	pthread_t threads[THREADS];
	t_fract		fracts[THREADS];

	int i = 0;
	while (i < THREADS)
	{
		fracts[i] = *fractol;
		fracts[i].start = HEIGHT / THREADS * i;
		printf("fracts[i].start = %d\n", fracts[i].start);
		pthread_create(&threads[i], NULL, (void *)mandelbrot, &fracts[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0,0);
}