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
#include <math.h>

# define WIDTH 1280
# define HEIGHT 720
typedef	struct	s_fract
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

}				t_fract;

typedef	struct	s_vars
{
	double			min_re;
	double			max_re;
	double			min_im;
	double			max_im;

	double			re_factor;
	double			im_factor;

	unsigned	int	iterations;
}				t_vars;

void	mandelbrot(t_fract *fractol);

#endif