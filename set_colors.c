/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:50:04 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/02/08 15:51:50 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int		get_color_green(t_fract *fractol, int iters)
{
	int red;
	int green;
	int blue;

	red = 0;
	green = (0x00FF00 >> 8) * iters / fractol->max_iterations;
	blue = 0;
	return (red << 16 | green << 8 | blue);
}

static	int		get_color_nice(t_fract *fractol, int iters)
{
	int		red;
	int		green;
	int		blue;
	double	k;

	k = (double)iters / fractol->max_iterations;
	red = 8.5 * pow(1 - k, 3) * k * 255;
	green = 15 * pow(1 - k, 2) * pow(k, 2) * 255;
	blue = 9 * (1 - k) * pow(k, 3) * 255;
	return (red << 16 | green << 8 | blue);
}

static	int		blue_color(t_fract *fractol, int iters)
{
	int		red;
	int		green;
	int		blue;
	double	k;

	k = (double)iters / fractol->max_iterations;
	red = 8.5 * pow(k, 3) * k * 255;
	green = 15 * pow(k, 2) * 55;
	blue = 21 * pow(k, 3) * 255;
	return (red << 16 | green << 8 | blue);
}

int				choose_color(t_fract *fractol, int iters)
{
	int color;

	color = 0;
	if (fractol->color == 0)
		color = get_color_green(fractol, iters);
	else if (fractol->color == 1)
		color = get_color_nice(fractol, iters);
	else if (fractol->color == 2)
		color = violet_color(fractol, iters);
	else if (fractol->color == 3)
		color = wbr_color(iters);
	else if (fractol->color == 4)
		color = blue_color(fractol, iters);
	else if (fractol->color == 5)
		color = byr_color(fractol, iters);
	return (color);
}
