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

int		get_color(t_fract *fractol, int iter)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 255 * iter / fractol->max_iterations;
	return (r | g | b);
}

void	init_vars(t_fract *fractol, t_vars *vars)
{
	vars->z_re = 0;
	vars->z_im = 0;
	vars->c_im = 0;
	vars->c_re = 0;

	// do with DELTA example
	vars->re_factor = (fractol->delta_re) / (WIDTH - 1);
	vars->im_factor = (fractol->delta_im) / (HEIGHT - 1);
	
	// vars->re_factor = (vars->max_re - vars->min_re) / (WIDTH - 1);
	// vars->im_factor = (vars->max_im - vars->min_im) / (HEIGHT - 1);
}

void	iters(t_fract *fractol, t_vars *vars, int x, int y)
{
	int		n;
	double	tmp;

	n = -1;
	while (++n < fractol->max_iterations)
	{
		tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re - vars->z_im * vars->z_im + vars->c_re;
		vars->z_im = 2 * vars->z_im * tmp + vars->c_im;
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break;
	}
	if (n == fractol->max_iterations)
	{
		fractol->image[x + y * WIDTH] = 0x000000;
	}
	else
		fractol->image[x + y * WIDTH] = get_color(fractol, n);
}

void	mandelbrot(t_fract *fractol)
{
	t_vars	vars;
	int		y;
	int		x;
	double tmp = 0;


	init_vars(fractol, &vars);
	y = fractol->start;
	while (y < HEIGHT / THREADS + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;

			// ============ Variant 1 ============
			// vars.c_re = x / fractol->zoom + fractol->min_re;
			// vars.c_im = y / fractol->zoom + fractol->min_im;

			// ============ Variant 2 ============
			// vars.c_re = fractol->min_re + x * vars.re_factor;
			// vars.c_im = fractol->min_im - (HEIGHT - y) * vars.im_factor;

			vars.c_re = fractol->min_re + x * vars.re_factor;
			vars.c_im = fractol->min_im - (HEIGHT - y) * vars.im_factor;

			iters(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	julia(t_fract *fractol)
{
	t_vars	vars;
	int		y;
	int		x;
	double tmp = 0;


	init_vars(fractol, &vars);
	vars.c_re = -0.7; // k_re
	vars.c_im = 0.288; // k_im

	y = fractol->start;
	while (y < HEIGHT / THREADS + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;

			vars.z_re = fractol->min_re + (x + 170) * vars.re_factor;
			vars.z_im = fractol->min_im - (HEIGHT - y) * vars.im_factor;

			// newRe = 1.5 * (x - WIDTH / 2) / (0.5 * WIDTH);
			// newIm = (y - HEIGHT / 2) / (0.5 * HEIGHT);

			iters(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	set_threads(t_fract *fractol, void *function)
{
	pthread_t threads[THREADS];
	t_fract		fracts[THREADS];

	int i = 0;
	while (i < THREADS)
	{
		fracts[i] = *fractol;
		fracts[i].start = HEIGHT / THREADS * i;
		// printf("fracts[i].start = %d\n", fracts[i].start);
		pthread_create(&threads[i], NULL, (void *)function, &fracts[i]);
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

void	choose_fractal(t_fract *fractol)
{
	if (fractol->type_fractal == MANDELBROT)
		set_threads(fractol, mandelbrot);
	else if (fractol->type_fractal == JULIA)
		set_threads(fractol, julia);
}