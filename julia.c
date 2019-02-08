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
#include <stdio.h>

void	julia(t_fract *fractol)
{
	t_vars	vars;
	int	x;
	int	y;

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
			iterations(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

void	burning_ship(t_fract *fractol)
{
	t_vars	vars;
	int	x;
	int	y;

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
