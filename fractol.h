/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:08:02 by vbrovenk          #+#    #+#             */
/*   Updated: 2019/01/27 17:08:05 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

# define WIDTH 640
# define HEIGHT 480
# define THREADS 4



// UBUTNTU Buttons
# define PLUS_ITER 65451
# define MINUS_ITER 65453

# define MOUSE_PLUS 4
# define MOUSE_MINUS 5



typedef	struct	s_fract
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	unsigned	int	iterations;

	int		start;

}				t_fract;

typedef	struct	s_vars
{
	double			min_re;
	double			max_re;
	double			min_im;
	double			max_im;

	double	z_re;
	double	z_im;
	double	c_im;
	double	c_re;
	double 			zoom;

	double			re_factor;
	double			im_factor;

}				t_vars;

void	mandelbrot(t_fract *fractol);
void	set_threads(t_fract *fractol);

#endif