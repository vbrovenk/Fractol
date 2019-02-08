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
			iterations(fractol, &vars, x, y);
			x++;
		}
		y++;
	}
}

