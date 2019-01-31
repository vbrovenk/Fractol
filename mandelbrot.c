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

void	init_vars(t_vars *vars)
{
	vars->min_re = -2.0;
	vars->max_re = 1.0;
	vars->min_im = -1.2;
	// vars->max_im = vars->min_im + (vars->max_re - vars->min_re) * (HEIGHT / WIDTH);
	vars->max_im = 2.0;
	
}

void	mandelbrot(t_fract *fractol)
{
	t_vars	vars;
	int		y;
	int		x;
	int		n;

	double	c_im;
	double	c_re;
	double	z_re;
	double	z_im;

	int is_inside;

	init_vars(&vars);
	vars.re_factor = (vars.max_re - vars.min_re) / (WIDTH - 1);
	vars.im_factor = (vars.max_im - vars.min_im) / (HEIGHT - 1);
	vars.iterations = 5;

// ============================================================================
	// y = 0;
	// while (y < HEIGHT)
	// {
	// 	c_im = vars.max_im - y * vars.im_factor;
	// 	// printf("c_im = %f\n", c_im);
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		c_re = vars.min_re + x * vars.re_factor;
	// 		// printf("c_re = %f\n", c_re);
	// 		z_re = c_re;
	// 		z_im = c_im;
	// 		is_inside = 1;
	// 		n = 0;
	// 		while (n < vars.iterations)
	// 		{
	// 			// printf("Res = %f\n", (z_re * z_re + z_im * z_im));
	// 			double temp = z_re * z_re + z_im * z_im;
	// 			if (temp > 4.0)
	// 			{
	// 				is_inside = 0;
	// 				break;
	// 			}
	// 			z_im = 2 * z_re * z_im + c_im;
	// 			z_re = z_re * z_re - z_im * z_im + c_re;
	// 			n++;
	// 		}
	// 		if (is_inside == 1)
	// 		{
	// 			printf("OK\n");
	// 			fractol->image[y * WIDTH + x] = 0xFF0000;
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
// ============================================================================
	
	for (x = 0; x < WIDTH; x++)
	{
		for (y = 0; y < HEIGHT; y++)
		{
			c_re = vars.min_re + x * vars.re_factor;
			c_im = vars.max_im - (HEIGHT - y) * vars.im_factor;

			z_re = 0;
			z_im = 0;
			
			n = 0;
			while (n < 20)
			{
				if ((z_re * z_re + z_im * z_im) > 4.0)
					break;
				tmp_re = z_re;
				tmp_im = z_im;
				z_re = tmp_re * tmp_re - tmp_im * tmp_im + c_re;
				z_im = 2 * tmp_re * tmp_im + c_im;
				n++;
			}
			int color = 0x0;
			fractol->image[x + y * WIDTH] = color;
		}
	}

	mlx_put_image_to_window(fractol->mlx_ptr, fractol->win_ptr, fractol->img_ptr, 0,0);
	
	// printf("min_re = %f\n", vars.min_re);
	// printf("max_re = %f\n", vars.max_re);
	// printf("min_im = %f\n", vars.min_im);
	// printf("max_im = %f\n", vars.max_im);

	// printf("re_factor = %f\n", vars.re_factor);
	// printf("im_factor = %f\n", vars.im_factor);
	
}
