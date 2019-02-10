/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:02:35 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/02/08 10:02:37 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fract *fractol)
{
	t_vars	vars;
	int		x;
	int		y;

	init_vars(fractol, &vars);
	vars.c_re = (double)(fractol->mouse_x - WIDTH / 2) / (WIDTH / 2);
	vars.c_im = (double)(fractol->mouse_y - HEIGHT / 2) / (HEIGHT / 2);
	y = fractol->start;
	while (y < HEIGHT / THREADS + fractol->start)
	{
		x = 0;
		while (x < WIDTH)
		{
			vars.z_re = 0;
			vars.z_im = 0;
			vars.z_re = fractol->min_re + x * vars.factor_re;
			vars.z_im = fractol->min_im + y * vars.factor_im;
			if (fractol->type_fractal == JULIA)
				iterations(fractol, &vars, x, y);
			else if (fractol->type_fractal == JULIA_5)
				julia5_iters(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	burning_ship(t_fract *fractol)
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
			iterations_ship(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	julia5_iters(t_fract *fractol, t_vars *vars, int x, int y)
{
	int	n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = fabs(vars->z_re * vars->z_re * vars->z_re * vars->z_re *
			vars->z_re - 10 * vars->z_re * vars->z_re * vars->z_re *
			vars->z_im * vars->z_im + 5 * vars->z_re * vars->z_im *
			vars->z_im * vars->z_im * vars->z_im + vars->c_re);
		vars->z_im = fabs(5 * vars->tmp * vars->tmp * vars->tmp * vars->tmp *
			vars->z_im - 10 * vars->tmp * vars->tmp * vars->z_im *
			vars->z_im * vars->z_im + vars->z_im * vars->z_im *
			vars->z_im * vars->z_im * vars->z_im + vars->c_im);
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}

void	last_fractal(t_fract *fractol, t_vars *vars, int x, int y)
{
	int n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re * vars->z_re * vars->z_re *
			vars->z_re - 10 * vars->z_re * vars->z_re * vars->z_re *
			vars->z_im * vars->z_im + 5 * vars->z_re * vars->z_im *
			vars->z_im * vars->z_im * vars->z_im + vars->c_re;
		vars->z_im = 5 * vars->tmp * vars->tmp * vars->tmp * vars->tmp *
			vars->z_im - 10 * vars->tmp * vars->tmp * vars->z_im *
			vars->z_im * vars->z_im + vars->z_im * vars->z_im *
			vars->z_im * vars->z_im * vars->z_im + vars->c_im;
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}
