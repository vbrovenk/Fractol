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

void	mandelbrot(t_fract *fractol)
{
	t_vars	vars;
	int		x;
	int		y;

	init_vars(fractol, &vars);
	y = fractol->start;
	while (y < HEIGHT / THREADS + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;
			vars.c_re = fractol->min_re + x * vars.factor_re;
			vars.c_im = fractol->min_im + y * vars.factor_im;
			iterations(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	tricorn(t_fract *fractol, t_vars *vars, int x, int y)
{
	int n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re - vars->z_im *
													vars->z_im + vars->c_re;
		vars->z_im = -2 * vars->z_im * vars->tmp + vars->c_im;
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}

void	general_loop(t_fract *fractol)
{
	t_vars	vars;
	int		x;
	int		y;

	init_vars(fractol, &vars);
	y = fractol->start;
	while (y < HEIGHT / THREADS + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;
			vars.c_re = fractol->min_re + x * vars.factor_re;
			vars.c_im = fractol->min_im + y * vars.factor_im;
			if (fractol->type_fractal == TRICORN)
				tricorn(fractol, &vars, x, y);
			else if (fractol->type_fractal == HALL)
				hall(fractol, &vars, x, y);
			else if (fractol->type_fractal == LEAF)
				leaf(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	hall(t_fract *fractol, t_vars *vars, int x, int y)
{
	int	n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = (vars->z_re * vars->z_re - vars->z_im * vars->z_im +
			vars->c_re) / (vars->c_re * vars->c_re + vars->c_im * vars->c_im);
		vars->z_im = 2 * vars->z_im * vars->tmp - vars->c_im /
			(vars->c_re * vars->c_re + vars->c_im * vars->c_im);
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}

void	leaf(t_fract *fractol, t_vars *vars, int x, int y)
{
	int	n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re - vars->z_im * vars->z_im +
			vars->c_re / (vars->c_re * vars->c_re + vars->c_im * vars->c_im);
		vars->z_im = 2 * vars->z_im * vars->tmp - vars->c_im /
			(vars->c_re * vars->c_re + vars->c_im * vars->c_im);
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}
