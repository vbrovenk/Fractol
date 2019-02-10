/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 13:37:14 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/02/10 13:37:15 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		wbr_color(int iters)
{
	int	color;
	int	tmp;

	tmp = iters % 3;
	if (tmp == 0)
		color = 0xffffff;
	else if (tmp == 1)
		color = 0x0000ff;
	else
		color = 0xff0000;
	return (color);
}

int		violet_color(t_fract *fractol, int iters)
{
	int		red;
	int		green;
	int		blue;
	double	k;

	k = (double)iters / fractol->max_iterations;
	red = (1 - k) * 45;
	green = k * 200;
	blue = (1 - k) + 75;
	return (red << 16 | green << 8 | blue);
}

int		byr_color(t_fract *fractol, int iters)
{
	int		red;
	int		green;
	int		blue;
	double	k;

	k = (double)iters / fractol->max_iterations;
	red = 8.5 * (1 - k) * pow(k, 3) * 255;
	green = 15 * pow(1 - k, 2) * pow(k, 2) * 255;
	blue = 9 * pow(1 - k, 2) * k * 255;
	return (red << 16 | green << 8 | blue);
}
