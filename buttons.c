/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:31:14 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/02/08 14:31:15 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				x_exit(void *param)
{
	param = NULL;
	system("leaks fractol");
	exit(0);
	return (0);
}

void		reset_params(t_fract *fractol)
{
	fractol->min_re = -2.0;
	fractol->min_im = -2.0;
	fractol->delta = 4.0;
}

int				choose_key(int key, t_fract *fractol)
{
	if (key == 53)
		x_exit(fractol);
	else if (key == PLUS_ITER)
		fractol->max_iterations += 1;
	else if (key == MINUS_ITER && fractol->max_iterations > 1)
		fractol->max_iterations -= 1;
	else if (key == ARROW_RIGHT)
		fractol->min_re += 0.085 * fractol->delta;
	else if (key == ARROW_LEFT)
		fractol->min_re -= 0.085 * fractol->delta;
	else if (key == ARROW_UP)
		fractol->min_im -= 0.085 * fractol->delta;
	else if (key == ARROW_DOWN)
		fractol->min_im += 0.085 * fractol->delta;
	else if (key == SPACE)
		fractol->space_on *= -1;
	else if (key == SHIFT)
		fractol->color = (fractol->color + 1) % 2;
	else if (key == BACKSPACE)
		reset_params(fractol);

	choose_fractal(fractol);
	return (0);
}

int			zoom_mouse(int key, int x, int y, t_fract *fractol)
{
	double	temp_re;
	double	temp_im;

	if (key == MOUSE_PLUS)
	{
		temp_re = fractol->min_re + ((double)x / WIDTH) * fractol->delta;
		temp_im = fractol->min_im + ((double)y / HEIGHT) * fractol->delta;
		fractol->delta *= 0.9;
		fractol->max_iterations += 1;
	}
	else if (key == MOUSE_MINUS && fractol->delta < 6)
	{
		temp_re = fractol->min_re + ((double)x / WIDTH) * fractol->delta;
		temp_im = fractol->min_im + ((double)y / HEIGHT) * fractol->delta;
		fractol->delta *= 1.1;
		if (fractol->max_iterations > 50)
			fractol->max_iterations -= 1;
	}
	else
		return (0);
	fractol->min_re = temp_re - ((double)x / WIDTH) * fractol->delta;
	fractol->min_im = temp_im - ((double)y / HEIGHT) * fractol->delta;
	choose_fractal(fractol);
	return (0);
}

int		move_mouse(int x, int y, t_fract *fractol)
{
	if (fractol->space_on == 1)
	{
		fractol->mouse_x = x;
		fractol->mouse_y = y;
	}
	choose_fractal(fractol);
	return (0);
}