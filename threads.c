/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:08:44 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/02/08 14:08:45 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_vars(t_fract *fractol, t_vars *vars)
{
	vars->z_re = 0.0;
	vars->z_im = 0.0;
	vars->c_re = 0.0;
	vars->c_im = 0.0;
	vars->factor_re = fractol->delta / (WIDTH - 1);
	vars->factor_im = fractol->delta / (HEIGHT - 1);
	vars->tmp = 0.0;
}

void	iterations(t_fract *fractol, t_vars *vars, int x, int y)
{
	int	n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = vars->z_re * vars->z_re - vars->z_im *
													vars->z_im + vars->c_re;
		vars->z_im = 2 * vars->z_im * vars->tmp + vars->c_im;
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}

void	iterations_ship(t_fract *fractol, t_vars *vars, int x, int y)
{
	int n;

	n = 0;
	while (n < fractol->max_iterations)
	{
		vars->tmp = vars->z_re;
		vars->z_re = fabs(vars->z_re * vars->z_re - vars->z_im *
													vars->z_im + vars->c_re);
		vars->z_im = fabs(2 * vars->z_im * vars->tmp + vars->c_im);
		if (vars->z_re * vars->z_re + vars->z_im * vars->z_im > 4)
			break ;
		n++;
	}
	if (n == fractol->max_iterations)
		fractol->image[x + y * WIDTH] = 0x000000;
	else
		fractol->image[x + y * WIDTH] = choose_color(fractol, n);
}

void	set_threads(t_fract *fractol, void *function)
{
	pthread_t	threads[THREADS];
	t_fract		fracts[THREADS];
	int			i;
	char		*tmp;

	i = 0;
	while (i < THREADS)
	{
		fracts[i] = *fractol;
		fracts[i].start = HEIGHT / THREADS * i;
		pthread_create(&threads[i], NULL, (void *)function, &fracts[i]);
		i++;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr,
														fractol->img_ptr, 0, 0);
	tmp = ft_itoa(fractol->max_iterations);
	mlx_string_put(fractol->mlx_ptr, fractol->win_ptr, 700, 10, 0x000000, tmp);
	free(tmp);
}

void	choose_fractal(t_fract *fractol)
{
	if (fractol->type_fractal == MANDELBROT)
		set_threads(fractol, mandelbrot);
	else if (fractol->type_fractal == JULIA)
		set_threads(fractol, julia);
	else if (fractol->type_fractal == SHIP)
		set_threads(fractol, burning_ship);
}
